#include "Motor.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "drive.cpp"
	
	
	void reset(int speed){
		while(1){
			int rotateA = nxt_motor_get_count(PORT_A);
			if (rotateA < -10){
				motorA.setPWM((-1) * speed);
			}	 
			else if (rotateA > 10){
				motorA.setPWM(speed);
			}
			else {
				motorA.setPWM(0);
                			break;
			}
		}
	}
	
	void angle(int rotate,int spin,int speed){
        while(1){
            int rotateA = nxt_motor_get_count(PORT_A);
            if (rotateA < (rotate + spin)){
                motorA.setPWM((-1) * speed);
            }
            else if (rotateA > (rotate + spin)){
                motorA.setPWM(speed);
            }
            else {
                motorA.setPWM(0);
                break;
            }
        }
	}
	
	int forward(int rotate,int spin,int lspeed,int rspeed){
		while(1){
			int rotateC = nxt_motor_get_count(PORT_C);
			if (rotateC > (rotate + ((-1) *spin))){
				motorB.setPWM((-1) * lspeed);
				motorC.setPWM((-1) * rspeed);
			}
            else if (rotateC < (rotate + ((-1) *spin))){
                motorB.setPWM(lspeed);
                motorC.setPWM(rspeed);
            }
			else {
				motorB.setPWM(0);
				motorC.setPWM(0);
                return rotateC;
			}
		}
	}
    
    int cturn(int rotate,int spin,int speed){
        while(1){
            int rotateC = nxt_motor_get_count(PORT_C);
            if (rotateC > (rotate + ((-1) *spin))){
                motorC.setPWM((-1) * speed);
            }
            else if (rotateC < (rotate + ((-1) *spin))){
                motorC.setPWM(speed);
            }
            else {
                motorC.setPWM(0);
                return rotateC;
            }
        }
    }

	void parallel_parking()
	{
		int rotateA;
		int rotateB;
		int rotateC;
		while(1)
		{			
			rotateA = nxt_motor_get_count(PORT_A);
			rotateB = nxt_motor_get_count(PORT_B);
			rotateC = nxt_motor_get_count(PORT_C);
			
			lcd.clear();
			lcd.putf("d", rotateC);
			lcd.disp();
					
			reset(-100);
            
			rotateC = forward(rotateC,450,40,40);
            
			angle(rotateA, 350,-100);
			rotateC = forward(rotateC,310,40,40);
            reset(-100);
			
            rotateC = forward(rotateC,-820,40,40);
            
            angle(rotateA,-650,-100);
            rotateC = cturn(rotateC,120,70);
            reset(-100);
            
			clock.wait(5000);
            
            angle(rotateA,-650,-100);
            rotateC = cturn(rotateC,-120,70);
            reset(-100);
            
            rotateC = forward(rotateC,820,40,40);
            
            angle(rotateA, 350,-100);
            rotateC = forward(rotateC,-310,40,40);
            reset(-100);
            
            clock.wait(15000);
		}
	}
}