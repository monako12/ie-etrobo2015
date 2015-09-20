extern "C"
{
	class Nihonbashi{
    int nowl;
    int ret_pid;
    int line;
  public:


    void nihon();
    void stop_ex();
  };

  void Nihonbashi::nihon()
  {
   motorB.setPWM(100);
   motorC.setPWM(100);
   clock.wait(300);
   motorC.setPWM(-100);
   motorB.setPWM(-100);
   clock.wait(700);
   motorB.setPWM(-70);
   motorC.setPWM(-70);


 }

 void Nihonbashi::stop_ex()
 {
  bar.search_bord();
  nihon();
}



}
