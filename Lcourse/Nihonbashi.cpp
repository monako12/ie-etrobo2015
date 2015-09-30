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
   clock.wait(250);
   motorC.setPWM(-85);
   motorB.setPWM(-85);
   clock.wait(550);
   motorC.setPWM(-50);
   motorB.setPWM(-40);
   clock.wait(1050);
   motorB.setPWM(-70);
   motorC.setPWM(-70);
   clock.wait(900);
   /*
   motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(80);
   motorA.setPWM(100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(50);
   motorA.setPWM(0);
   motorB.setPWM(-100);
   motorC.setPWM(-100);*/
   /*
   motorB.setPWM(40);
   motorC.setPWM(40);
   clock.wait(400);
   motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(500);
   motorA.setPWM(0);
   motorB.setPWM(-20);
   motorC.setPWM(-80);
   clock.wait(300);
   motorA.setPWM(100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(500);
   */
   /*
   motorB.setPWM(50);
   motorC.setPWM(50);
   clock.wait(1000);
   */
   motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(450);
   motorA.setPWM(0);



   while(sensor.nowlight() > sen.ret_black()){
   motorB.setPWM(-20);
   motorC.setPWM(-100);
 }
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(200);
   par.reset(100);








 }

 void Nihonbashi::stop_ex()
 {
  bar.search_bord(16,false);
  
  drive.motor_stop();
  par.reset(100);
  clock.wait(200);
  

  nihon();
}



}
