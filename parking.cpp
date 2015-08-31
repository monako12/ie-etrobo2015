#include "Motor.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    class Parking{
    public:
        int nrotate;
        int rotate;
        
        sensor sensor;
        Cal cal;
        
        void reset(int speed){
            while(1){
                nrotate = nxt_motor_get_count(PORT_A);
                if (nrotate < -10){
                    motorA.setPWM(speed);
                }
                else if (nrotate > 10){
                    motorA.setPWM((-1) * speed);
                }
                else {
                    motorA.setPWM(0);
                    break;
                }
            }
        }
        
        void angle(int number,int speed){
            rotate = nxt_motor_get_count(PORT_A);
            while(1){
                nrotate = nxt_motor_get_count(PORT_A);
                if (nrotate < (rotate + number)){
                    motorA.setPWM(speed);
                }
                else if (nrotate > (rotate + number)){
                    motorA.setPWM((-1) * speed);
                }
                else {
                    motorA.setPWM(0);
                    break;
                }
            }
        }
        void forward(int number,int lspeed,int rspeed,int tire){
            if (tire == 0){
                rotate = nxt_motor_get_count(PORT_B);
            } else if (tire == 1) {
                rotate = nxt_motor_get_count(PORT_C);
            }
            while(1){
                if (tire == 0){
                    nrotate = nxt_motor_get_count(PORT_B);
                } else if (tire == 1) {
                    nrotate = nxt_motor_get_count(PORT_C);
                }
                lcd.clear();
                lcd.putf("d", nrotate);
                lcd.disp();
                if (nrotate > (rotate + ((-1) * number))){
                    motorB.setPWM((-1) * lspeed);
                    motorC.setPWM((-1) * rspeed);
                }
                else if (nrotate < (rotate + ((-1) * number))){
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
            while(1)
            {
                reset(100);
                forward(100,40,40,1);
                //前輪角度
                angle(700,100);
                //回転
                forward(290,80,0,0);
                
                //角度直し
                reset(100);
                //バック
                forward(-780,40,40,1);
                clock.wait(5000);
                
                black(40,40);
                forward(130,40,40,1);
                
                angle(-700,100);
                black(0,80);
                reset(100);
                
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
        
        void parallel_parking()
        {
            while(1)
            {
                reset(100);
                
                forward(450,40,40,1);
                
                angle(350,100);
                forward(310,40,40,1);
                reset(100);
                
                forward(-820,40,40,1);
                
                angle(-650,100);
                forward(120,0,70,1);
                reset(100);
                
                clock.wait(5000);
                
                
                //sensor
                angle(680,100);
                forward(290,80,0,0);
                reset(100);
                black(40,40);
                
                forward(90,40,40,1);
                
                angle(-700,100);
                black(0,80);
                reset(100);
                
                clock.wait(1000);
                break;
                
                
                /*
                 //手動
                 angle(rotateA,680,100);
                 forward(290,80,0,0);
                 reset(100);
                 forward(150,40,40,1);
                 angle(rotateA,-700,100);
                 forward(290,0,80,1);
                 reset(100);
                 clock.wait(10000);
                 */
            }
        }

    };
}