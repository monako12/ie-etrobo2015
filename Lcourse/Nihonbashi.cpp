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
   motorB.setPWM(100);
   motorC.setPWM(100);
   clock.wait(200);
   motorC.setPWM(-75);
   motorB.setPWM(-75);
   clock.wait(200);
   drive.motor_stop();
   motorC.setPWM(-73);
   motorB.setPWM(-63);
   clock.wait(250);
   drive.motor_stop();
   par.reset(100);
   motorC.setPWM(-45);
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
   motorB.setPWM(-10);
   motorC.setPWM(-40);
i++;
   if(i > 2500){
    while(i < 0)
   {
    i--;
    motorB.setPWM(10);
    motorC.setPWM(40);
   }
   motorA.setPWM(100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(200);
   motorA.setPWM(0);
   while(sensor.nowlight() > sen.ret_black()){
   motorB.setPWM(-10);
   motorC.setPWM(-40);
   i = 2000;
 }
 if( i == 2000){while(1){drive.motor_stop();}break;}
}


 }
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(200);
   par.reset(100);








 }

 void Nihonbashi::stop_ex()
 {motorA.setPWM(-100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(450);
   motorA.setPWM(0);
  while(sensor.nowlight() > sen.ret_black()){
   motorB.setPWM(-10);
   motorC.setPWM(-40);
   i++;
   if(i > 210000)
   {
    break;
   }
 }
 if(sensor.nowlight() >= sen.ret_black()){
  while(i < 0)
   {
    i--;
    motorB.setPWM(10);
    motorC.setPWM(40);
   }
   motorA.setPWM(100);
   motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(650);
   motorA.setPWM(0);
   while(sensor.nowlight() > sen.ret_black()){
   motorB.setPWM(-40);
   motorC.setPWM(-10);

 }
 motorB.setPWM(0);
   motorC.setPWM(0);
   clock.wait(200);
   par.reset(100);



 }


  bar.search_bord2(23,false);
  
  drive.motor_stop();
  par.reset(100);
  clock.wait(200);
  

  nihon();
}



}
