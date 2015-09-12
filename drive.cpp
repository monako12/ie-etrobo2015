//made by okada
#include "Motor.h"
#include "math.h"
#include "stdlib.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#define MOTOR_B 0
#define MOTOR_C 1

  Motor motorA(PORT_A);
  Motor motorB(PORT_B);
  Motor motorC(PORT_C);
  Clock clock;
  Lcd lcd;
  SensorGet sensor;
  Cal cal;
  
  class Drive{
  public:
    int nrotate; //現在の回転数
    int srotate; //初期の回転数
      
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
      int power = 0;
      if(line > 0){
	if(motorA.getCount() >= -80){
	  motorA.setPWM(-60);
	}else{
	  motorA.setPWM(0);
	}
	if(pid < 0)pid=0;
	if((-pid + position()) < - 100)power = -100;
	motorB.setPWM(-pid);
	motorC.setPWM(power);
	distance = position();
      }else{
	motor_stop();
	clock.wait(1000);
	/*motor_count_reset();	
	while(position()<(-distance/2)){
	  back(distance);
	  lcd.clear();
	  lcd.putf("dn",position());
	  lcd.putf("d", (-distance/2));
	  lcd.disp();
	}
	  motor_stop();*/
	motorA_position_reset();
	//clock.wait(1000);
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
      
    void angle(int number,int speed){
        srotate = nxt_motor_get_count(PORT_A);
        while(1){
            nrotate = nxt_motor_get_count(PORT_A);
            if (nrotate < (srotate + number)){
                motorA.setPWM(speed);
            }
            else if (nrotate > (srotate + number)){
                motorA.setPWM((-1) * speed);
            }
            else {
                motorA.setPWM(0);
                break;
            }
        }
    }
    
    void forward(int number,int lspeed,int rspeed,int tire){
        if (tire == MOTOR_B){
            srotate = nxt_motor_get_count(PORT_B);
        } else if (tire == MOTOR_C) {
            srotate = nxt_motor_get_count(PORT_C);
        }
        while(1){
            if (tire == MOTOR_B){
                nrotate = nxt_motor_get_count(PORT_B);
            } else if (tire == MOTOR_C) {
                nrotate = nxt_motor_get_count(PORT_C);
            }
            if (nrotate > (srotate + ((-1) * number))){
                motorB.setPWM((-1) * lspeed);
                motorC.setPWM((-1) * rspeed);
            }
            else if (nrotate < (srotate + ((-1) * number))){
                motorB.setPWM(lspeed);
                motorC.setPWM(rspeed);
            }
            else {
                motorB.setPWM(0);
                motorC.setPWM(0);
                break;
            }
        }
    }
      
    void bforward(int lspeed,int rspeed){
        while(1){
            int now = sensor.nowlight(0);
            int ava = sensor.ret_avarage();
            int color = cal.cur_ava(now,(double)ava);
            if (color < 0){
                motorB.setPWM(0);
                motorC.setPWM(0);
                break;
            }
            else if (color > 0){
            motorB.setPWM((-1) * lspeed);
            motorC.setPWM((-1) * rspeed);
            }
        }
    }

};
  
}
