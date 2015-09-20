using namespace ecrobot;
extern "C"
{
  SensorGet sen;
  Cal calcu;
  Drive drive;

  int Execute_Touch_Pressed = sen.lightavarage(); //どのタイミングで実行されるかわからん
  class PIDrun{
    int ava;
    int nowl;
    int ret_pid;
    int line;
  public:

    void pid_running(int);
    void pid_dash();
    int line_side_check();
    int fix_position();
    void parameter();
    void display();
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
  }

  void PIDrun::display(){
    lcd.clear();
    lcd.putf("sdn","position: ", drive.position(),5);
    lcd.putf("sdn","ava", sen.ret_avarage(),5);
    lcd.putf("sdn","nowlight: ", nowl, 5);
    lcd.putf("sdn","pid_value: ", ret_pid,5);
    lcd.putf("sd","line: ", line, 5);
    lcd.disp();
  }

  void PIDrun::pid_running(int hoge){
    parameter();
    display();
    if(hoge == 1){
      drive.Left_Edge_Trace(ret_pid,line);/*左側のエッジ(黒の左側)を走る*/
    }
    else{
      drive.Right_Edge_Trace(ret_pid,line);/*右側のエッジ(黒の右側)を走る*/
    }
    clock.wait(1);
  }

  void PIDrun::pid_dash(){
    parameter();
    drive.dash(ret_pid,line);
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
	find_out_side = drive.LeftSide_line_check(nowl, retb()) == 1? 0:2;
	if(find_out_side == 0)break;
      }
      drive.motor_stop();
      drive.Return_to_position(goto_side);
      clock.wait(100);
      
      if(find_out_side != 0){ //左にラインが見つからなかった時
	drive.motor_count_reset();
	goto_side = false;
	while(drive.position() >= roop_range){ //右探査
	  parameter();
	  display();
	  find_out_side = drive.RightSide_line_check(nowl, retb()) == 1? 1:2;
	  if(find_out_side == 1)break;
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
