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
        
        sensor sensor;
        Cal cal;
        
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
        
        void forward(int spin,int lspeed,int rspeed,int flag){
            int nrotate;
            int rotate;
            if (flag == 0){
                rotate = nxt_motor_get_count(PORT_B);
            } else if (flag == 1) {
                rotate = nxt_motor_get_count(PORT_C);
            }
            while(1){
                if (flag == 0){
                    nrotate = nxt_motor_get_count(PORT_B);
                } else if (flag == 1) {
                    nrotate = nxt_motor_get_count(PORT_C);
                }
                lcd.clear();
                lcd.putf("d", nrotate);
                lcd.disp();
                if (nrotate > (rotate + ((-1) *spin))){
                    motorB.setPWM((-1) * lspeed);
                    motorC.setPWM((-1) * rspeed);
                }
                else if (nrotate < (rotate + ((-1) *spin))){
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
        
        void black(int lspeed,int rspeed){
            while(1){
                int now = sensor.nowlight(0);
                int ava = sensor.ret_avarage();
                int color = cal.cur_ava(now,(double)ava);
                
                lcd.clear();
                lcd.putf("d", ava);
                lcd.disp();
                
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
        
        void right_angle_parking()
        {
            int rotateA;
            int rotateB;
            int rotateC;
            while(1)
            {
                rotateA = nxt_motor_get_count(PORT_A);
                rotateB = nxt_motor_get_count(PORT_B);
                rotateC = nxt_motor_get_count(PORT_C);
                
                reset(-100);
                forward(100,40,40,1);
                //前輪角度
                angle(rotateA,700,-100);
                //回転
                forward(290,80,0,0);
                
                //角度直し
                reset(-100);
                //バック
                forward(-780,40,40,1);
                clock.wait(5000);
                
                black(40,40);
                forward(130,40,40,1);
                
                angle(rotateA,-700,-100);
                black(0,80);
                reset(-100);
                
                clock.wait(10000);
                break;
                /*
                 //前進
                 rotateC = forward(rotateC,780,40,40);
                 //角度
                 angle(rotateA,700,-100);
                 //回転
                 rotateB = turn(rotateB,-290,80);
                 //角度直し
                 reset(-100);
                 clock.wait(10000);
                 */
            }
        }
    };
}