#include "Motor.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    class RaPa{
        public:
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
	
        int turn(int rotate,int spin,int speed){
            while(1){
                int rotateB = nxt_motor_get_count(PORT_B);
                lcd.clear();
                lcd.putf("d", (rotate + ((-1) *spin)));
                lcd.disp();
                if (rotateB > (rotate + ((-1) *spin))){
                    motorB.setPWM((-1) * speed);
                }
                else if (rotateB < (rotate + ((-1) *spin))){
                    motorB.setPWM(speed);
                }
                else {
                    motorB.setPWM(0);
                    return rotateB;
                }
            }
        }
	
        int forward(int rotate,int spin,int lspeed,int rspeed){
            while(1){
                int rotateC = nxt_motor_get_count(PORT_C);
                lcd.clear();
                lcd.putf("d", (rotate + ((-1) *spin)));
                lcd.disp();
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
	
        int right_angle_parking()
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
                lcd.putf("d", rotateB);
                lcd.disp();
					
                reset(130);
                //前輪角度
                angle(rotateA,700,-100);
                //回転
                rotateB = turn(rotateB,290,80);
            
                //角度直し
                reset(130);
                //バック
                rotateC = forward(rotateC,-780,40,40);
                clock.wait(5000);
                //前進
                rotateC = forward(rotateC,780,40,40);
                //角度
                angle(rotateA,700,-100);
                //回転
                rotateB = turn(rotateB,-290,80);
                //角度直し
                reset(-100);
                clock.wait(10000);
            }
        }
    };
}