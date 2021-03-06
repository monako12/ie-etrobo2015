using namespace ecrobot;
extern "C"
{
  SensorGet sen;
  Cal calcu;
  Drive drive;
  CatchGray graycount;

  int Execute_Touch_Pressed = sen.lightavarage(); //どのタイミングで実行されるかわからん
  int search = 0;
  int gcount = 0;
  class PIDrun{
    int ava;
    int nowl;
    int ret_pid;
    int line;
		int gray;
  public:

    void pid_running(int,int,int,int);
    void pid_dash();
		void pid_dash_left();
    int line_side_check();
    int fix_position();
    void parameter();
    void display();
		bool gray_discover();
    int retb();
    int retw();
  };

  int PIDrun::retb(){
    int black = sen.ret_black();
    return(black);
  }

  int PIDrun::retw(){
    int white = sen.ret_white();
    return(white);
  }

  void PIDrun::parameter(){
    ava = sen.ret_Threshold(); //変更の可能性あり
    nowl = sen.nowlight();
    ret_pid = calcu.p_i_d(ava,nowl);
    line = calcu.cur_ava(nowl,ava);
		gray = sen.ret_gray();
//		search = graycount.catch_g(nowl,search,ava);
//		gcount = graycount.gray_count(gcount,search);
  }

	bool PIDrun::gray_discover(){
		bool huga = false;
		search = graycount.catch_g(nowl,search,retb(),gray);
		gcount = graycount.gray_count(gcount,search);
		if(gcount > 1000 && search == 0){
			drive.motor_stop();
			clock.wait(10000);
			huga = true;
		}
		return(huga);
	}

  void PIDrun::display(){
    lcd.clear();
	lcd.putf("dn",search,5);
	lcd.putf("dn",gcount,5);
    lcd.putf("sdn","position: ", drive.position(),5);
//    lcd.putf("sdn","ava", sen.ret_avarage(),5);
//    lcd.putf("sdn","nowlight: ", nowl, 5);
//    lcd.putf("sdn","pid_value: ", ret_pid,5);
//    lcd.putf("sd","line: ", line, 5);
    lcd.disp();
  }

  void PIDrun::pid_running(int hoge,int f,int width,int Apower){
    parameter();
    display();
    if(hoge == 1){
      drive.Left_Edge_Trace(ret_pid,line,width,Apower,f);/*左側のエッジ(黒の左側)を走る*/
    }
	else if(hoge == 2){
	  drive.Barcode_pid_run(ret_pid,line,f);
	}
	else if(hoge == 3){
	  drive.slow_Trace(ret_pid,line,f);
	}
    else{
      drive.Right_Edge_Trace(ret_pid,line,width,Apower,f);/*右側のエッジ(黒の右側)を走る*/
    }
    clock.wait(1);
  }

  void PIDrun::pid_dash(){
    parameter();
    drive.dash(ret_pid,line);
  }

	void PIDrun::pid_dash_left(){
		parameter();
		drive.dash_left(ret_pid,line);
	}

  int PIDrun::line_side_check(){
    int find_out_side = 2;
    int roop_range = -300;
    int rooping_serch_count = 0;
    bool goto_side;
    drive.motor_count_reset();
    while(find_out_side == 2){
      goto_side = true;
      roop_range = (roop_range * (10 + rooping_serch_count))/10;
      while(drive.position() >= roop_range){ //左探査
	parameter();
	display();
	//find_out_side = drive.LeftSide_line_check(nowl, retb()) == 1? 0:2;
	find_out_side = drive.RightSide_line_check(nowl, retb()) == 1? 1:2;
	//if(find_out_side == 0)break;
	if(find_out_side == 1)break;
      }
      drive.motor_stop();
      drive.Return_to_position(goto_side);
      clock.wait(100);

      //if(find_out_side != 0){ //左にラインが見つからなかった時
      if(find_out_side != 1){
	drive.motor_count_reset();
	goto_side = false;
	while(drive.position() >= roop_range){ //右探査
	  parameter();
	  display();
	  //find_out_side = drive.RightSide_line_check(nowl, retb()) == 1? 1:2;
	  find_out_side = drive.LeftSide_line_check(nowl, retb()) == 1? 0:2;
	  //if(find_out_side == 1)break;
	  if(find_out_side == 0)break;
	}
	drive.motor_stop();
	clock.wait(10);
	drive.Return_to_position(goto_side);
	drive.motor_stop();
	clock.wait(10);
      }
      rooping_serch_count++;
    }
    return find_out_side;
  }

  int PIDrun::fix_position(){
      int distance = 114514;
      int line_side;
      drive.motor_count_reset();
      line_side = line_side_check();
      if(line_side == 0){ //左側にラインがある時の修正処理
	while(distance > 35){
	  parameter();
	  display();
	  distance = drive.fix_position(ret_pid, nowl, line_side, distance, retb());
	}
      }else if(line_side == 1){ //右側にラインがある時の修正処理
	while(distance > 35){
	  parameter();
	  display();
	  distance = drive.fix_position(ret_pid, nowl, line_side, distance, retb());
	}
      }
      return line_side;
  }
}
