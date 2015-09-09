//made by okada
#include "Motor.h"
#include "math.h"
#include "stdlib.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{

  Motor motorA(PORT_A);
  Motor motorB(PORT_B);
  Motor motorC(PORT_C);
  Clock clock;
  Lcd lcd;
  
  class Drive{
  public:
    int Acount(){
      return(motorA.getCount());
    }
    
    int Bcount(){
      return(motorB.getCount());
    }

    int Ccount(){
      return(motorC.getCount());
    }

    int position(){
      return((Bcount()+Ccount())/2);
    }

    void motor_count_reset(){
      motorB.reset();
      motorC.reset();
    }

    void motor_stop(){
      motorB.setPWM(0);
      motorC.setPWM(0);
    }

    void curve(int sum,int line){

    if(sum > 100){

      if(line < 0)
      {
        if(motorA.getCount() < 200)
        {
          motorA.setPWM(50);
        }else{
          motorA.setPWM(0);
        }
      }
      if(line > 0)
      {
        if(motorA.getCount() > -200){

          motorA.setPWM(-50);
        }else{
          motorA.setPWM(0);
        }

      }

    }

  }

    void mode_Black_Left(int pid,int line){
      if(line < 0){
	if(motorA.getCount() <= 200){
	  motorA.setPWM(80);
	}else{
	  motorA.setPWM(0);
	}
      }
      if(line > 0){
	if(motorA.getCount() >= -200){
	  motorA.setPWM(-80);
	}else{
	  motorA.setPWM(0);
	}
      }
      int b;
      int c;
      if(pid < 0){
	b = -35 + (pid/4);
	c = -35 - (pid/4);
      }else{
	b = -30 + (pid/3);
	c = -40 - (pid/4);
      }
      motorC.setPWM(c);
      motorB.setPWM(b);
    }
    
    void mode_Black_Right(int pid,int line){
      if(line < 0){
	if(motorA.getCount() >= -200){
	  motorA.setPWM(-80);
	}else{
	  motorA.setPWM(0);
	}
      }
      if(line > 0){
	if(motorA.getCount() <= 200){
	  motorA.setPWM(80);
	}else{
	  motorA.setPWM(0);
	}
      }
      int b;
      int c;
      if(pid < 0){
	b = -35 - (pid/4);
	c = -35 + (pid/4);
      }else{
	b = -40 - (pid/4);
	c = -30 + (pid/3);
      }
      
      motorC.setPWM(c);
      motorB.setPWM(b);
      
    }
    
    void dash(int pid,int line){
      if(line < 0){
	if(motorA.getCount() <= -40){
	  motorA.setPWM(-25);
	}else{
	  motorA.setPWM(0);
	}
      }
      if(line > 0){
	if(motorA.getCount() >= 40){
	  motorA.setPWM(25);
	}else{
	  motorA.setPWM(0);
	}
      }
      
    int b;
    int c;
    if(pid < 0){
      b = -85 + (pid/4);
      c = -85 - (pid/4);
    }else{
      b = -79 + (pid/3);
      c = -92 - (pid/4);
    }
    motorC.setPWM(c);
    motorB.setPWM(b);
    
    }
    
    int fix_position(int pid, int line, int distance){
      motor_count_reset();
      if(line > 0){
	if(motorA.getCount() >= -80){
	  motorA.setPWM(-60);
	}else{
	  motorA.setPWM(0);
	}
	motorB.setPWM(-pid);
	motorC.setPWM(-pid+(position()));
	distance = position();
      }else{
	motor_stop();
	clock.wait(10000);
	motor_count_reset();
	while(position()<(-distance/2)){
	  back(distance);
	  lcd.clear();
	  lcd.putf("dn",position());
	  lcd.putf("d", (-distance/2));
	  lcd.disp();
	}
	motor_stop();
	motorA_position_reset();
	clock.wait(1000);
      }
      return position();
    }
    
    void back(int distance){
      if(motorA.getCount() >= -600){
	motorA.setPWM(-100);
      }else{
	motorA.setPWM(0);
	motorC.setPWM(60);
	motorB.setPWM(-40);
      }
    }
    
    void motorA_position_reset(){
      motorA.setPWM(-nxt_motor_get_count(PORT_A));
    }

};
  
}
