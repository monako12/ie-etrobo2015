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
   clock.wait(200);
   motorC.setPWM(-100);
   motorB.setPWM(-100);
   clock.wait(400);
   motorB.setPWM(-70);
   motorC.setPWM(-70);
   clock.wait(800);
   motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(70);
   motorA.setPWM(100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(50);
   motorA.setPWM(0);
   motorB.setPWM(-100);
   motorC.setPWM(-100);
   clock.wait(500);
   while(sensor.nowlight() > sen.ret_black()){
   motorB.setPWM(50);
   motorC.setPWM(50);
 }
   




 }

 void Nihonbashi::stop_ex()
 {
  bar.search_bord(34);

  nihon();
}



}
