
using namespace ecrobot;

extern "C"
{
  sensor sen;
  Cal calcu;
  Drive drive;

  int ava = sen.lightavarage();

  class PIDrun{
    int nowl;
    int ret_pid;
    int line;
  public:

    void pid_running(bool);
    void pid_dash();
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

  void PIDrun::fix_position(){
    drive.motor_count_reset();
    int distance = 100;
    while(1){
      parameter();
      display();
      distance = drive.fix_position(ret_pid, line, distance);
    }
  }

}
