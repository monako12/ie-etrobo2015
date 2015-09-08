
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
  };

  int PIDrun::parameter(){
    nowl = sen.nowlight(ava);
    ret_pid = calcu.p_i_d(ava,nowl);
    line = calcu.cur_ava(nowl,ava);
    return ret_pid;
  }

  void PIDrun::display(){
    lcd.clear();
    lcd.putf("dn", drive.position());
    lcd.putf("d", ret_pid);
    lcd.disp();
  }
  
  void PIDrun::pid_running(bool hoge){
    //			int sum = sen.ret_sum();
    //			int pos = drive.position();
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
    int distance = 100;
    while(distance > 0 || -5 > distance){
      parameter();
      display();
      distance = drive.fix_position(ret_pid, line, distance);
    }
  }
  
}
