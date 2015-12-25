extern "C"
{
	class Nihonbashi{
    int nowl;
    int ret_pid;
    int line;
    int i;
  public:


    void nihon();
    void stop_ex();
  };

  void Nihonbashi::nihon()
  {
   //日本橋に前足をかける
   motorB.setPWM(100);
   motorC.setPWM(100);
   clock.wait(200);
   motorC.setPWM(-90);
   motorB.setPWM(-90);
   clock.wait(250);
   drive.motor_stop();
   motorC.setPWM(-68);
   motorB.setPWM(-72);
   clock.wait(250);
   drive.motor_stop();
   par.reset(40);
   motorC.setPWM(-60);
   motorB.setPWM(-60);
   clock.wait(300);
   /*
   clock.wait(1000);
   motorC.setPWM(-62);
   motorB.setPWM(-60);
   clock.wait(1050);
   motorB.setPWM(-70);
   motorC.setPWM(-70);
   clock.wait(1000);
   
   drive.motor_stop();
   clock.wait(200);
   drive.bforward2(20,20);
   
   
   motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(400);
   motorA.setPWM(0);



   while(sensor.nowlight() > sen.ret_black()+30){
   motorB.setPWM(-5);
   motorC.setPWM(-20);
   }
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(200);
   par.reset(100);
   */








 }

 void Nihonbashi::stop_ex()
 {

  bar.search_bord2(23,false);
  
  drive.motor_stop();
  par.reset(100);
  clock.wait(200);
  

  nihon();
}



}
