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
      motorA.setPWM(0);
      motorB.setPWM(0);
      motorC.setPWM(0);
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

    int RightSide_line_check(int light_value, int black){
      bool find_out = 0;
      if(motorA.getCount() <= 80){
	motorA.setPWM(60);
      }else{
	motorA.setPWM(0);
      }
      motorB.setPWM(-60);
      motorC.setPWM(-20);
      if(light_value <= black + 10){
	find_out = 1;
      }
      return find_out;
    }

    int LeftSide_line_check(int light_value, int black){
      bool find_out = 0;
      if(motorA.getCount() >= -80){
	motorA.setPWM(-60);
      }else{
	motorA.setPWM(0);
      }
      motorB.setPWM(-20);
      motorC.setPWM(-60);
      if(light_value == black){
	find_out = 1;
      }
      return find_out;
    }

    void Return_to_position(bool side){
      if(side == true){
	while(0 >= position()){
	  motorB.setPWM(20);
	  motorC.setPWM(60);
	}
      }else{
	while(0 >= position()){
	  motorB.setPWM(60);
	  motorC.setPWM(20);
	}
      }
    }

    int fix_position(int pid, int line, int distance){
      int B_power = 0;
      int C_power = 1;
      if(line >= 0){
	if(motorA.getCount() >= -80){
	  motorA.setPWM(-60);
	}else{
	  motorA.setPWM(0);
	}
	B_power = power_Adjustment(pid, B_power);
	C_power = power_Adjustment(pid, C_power);
	motorB.setPWM(B_power);
	motorC.setPWM(C_power);
	distance = position();
      }else{
	motor_stop();
	clock.wait(1000);
	motor_count_reset();	
	while(position()<(-distance/2)){
	  back();
	}
	  motor_stop();
	  motorA_position_reset();
	clock.wait(1000);
      }
      return position();
    }
    
    void back(){
      if(motorA.getCount() >= -300){
	motorA.setPWM(-80);
      }else{
	motorA.setPWM(0);
	motorC.setPWM(50);
	motorB.setPWM(0);
      }
    }

    int power_Adjustment(int pid, int power){
      if(-pid <= -60) pid = 60;
      if(power == 1){
	return -pid;
      }else{
	if((-pid - position()/3) <= -30) return -30;
	else return (-pid -position()/3);
      }
    }
    
    void motorA_position_reset(){
      while(motorA.getCount() >= 5 || -5 >= motorA.getCount()){
	if(motorA.getCount() <= 0){
	  motorA.setPWM(40);
	}else{
	  motorA.setPWM(-40);
	}
	lcd.clear();
	lcd.putf("sdn", "motorACount:", motorA.getCount(),5);
	lcd.disp();	    
      }
    }

};
  
}
