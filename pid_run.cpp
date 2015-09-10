using namespace ecrobot;
extern "C"
{
  sensor sen;
  Cal calcu;
  Drive drive;

  class PIDrun{
    int ava;
    int nowl;
    int ret_pid;
    int line;
  public:

    void pid_running(bool);
    void pid_dash();
    int line_side_check();
    void fix_position();
    int parameter();
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

  int PIDrun::parameter(){
    ava = sen.lightavarage();
    nowl = sen.nowlight(ava);
    ret_pid = calcu.p_i_d(ava,nowl);
    line = calcu.cur_ava(nowl,ava);
    return ret_pid;
  }

  void PIDrun::display(){
    lcd.clear();
    lcd.putf("sdn","position: ", drive.position(),5);
    lcd.putf("sd","pid_value: ", ret_pid,5);
    lcd.disp();
  }

  void PIDrun::pid_running(bool hoge){
    parameter();
    display();
    if(hoge == true){
      drive.mode_Black_Right(ret_pid,line);/*左側のエッジ(黒の左側)を走る*/
    }
    else{
      drive.mode_Black_Left(ret_pid,line);/*右側のエッジ(黒の右側)を走る*/
    }
  }

  void PIDrun::pid_dash(){
    parameter();
    drive.dash(ret_pid,line);
  }

  int PIDrun::line_side_check(){
    int find_out_side = 2;
    bool goto_side = false;
    drive.motor_count_reset();
    while(drive.position() >= -100){
      parameter();
      display();
      find_out_side = drive.RightSide_line_check(nowl, retb()) == 1? 1:2;
      if(find_out_side == 1)break;
    }
    drive.motor_stop();
    drive.Return_to_position(goto_side);
    
    if(find_out_side != 1){
      drive.motor_count_reset();
      goto_side = true;
      while(drive.position() >= -100){
	parameter();
	display();
	find_out_side = drive.LeftSide_line_check(nowl, retb()) == 1? 0:2;
	if(find_out_side == 0)break;
      }
      drive.motor_stop();
      drive.Return_to_position(goto_side);
    }
    return find_out_side;
  }
  
  void PIDrun::fix_position(){
    //if(line_side_check() == 0){
      int distance = 100;
      drive.motor_count_reset();
      while(1){
	parameter();
	display();
	distance = drive.fix_position(ret_pid, line, distance);
      }
      //}
  }
  
}


