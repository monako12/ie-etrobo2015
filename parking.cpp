#include "Motor.h"
#include "Clock.h"
#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define MOTOR_B 0
#define MOTOR_C 1
    
    class Parking{
    public:
        int nrotate; //現在の回転数
        int srotate; //初期の回転数
        
        sensor sensor;
        Cal cal;
        
        //前輪の回転数をリセットする
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
        
        //前輪を回転させる
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
        
        //後輪を回転させる
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
        
        //黒判定により後輪を回転させる
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
        
        void right_angle_parking()
        {
            while(1)
            {
                reset(100);
                forward(100,40,40,MOTOR_C);
                //前輪角度
                angle(700,100);
                //回転
                forward(290,80,0,MOTOR_B);
                
                //角度直し
                reset(100);
                //バック
                forward(-780,40,40,MOTOR_C);
                clock.wait(5000);
                
                bforward(40,40);
                forward(130,40,40,MOTOR_C);
                
                angle(-700,100);
                bforward(0,80);
                reset(100);
                
                clock.wait(1000);
                break;
                /*
                 //前進
                 forward(780,40,40,1);
                 //角度
                 angle(700,100);
                 //回転
                 forward(-290,80,0,0);
                 //角度直し
                 reset(100);
                 clock.wait(10000);
                 */
            }
        }
        
        void parallel_parking()
        {
            while(1)
            {
                reset(100);
                
                forward(1400,40,40,MOTOR_C);
                
                angle(350,100);
                forward(310,40,40,MOTOR_C);
                reset(100);
                
                forward(-820,40,40,MOTOR_C);
                
                angle(-650,100);
                forward(100,0,70,MOTOR_C);
                reset(100);
                
                clock.wait(5000);
                
                
                //sensor
                angle(680,100);
                forward(290,80,0,MOTOR_B);
                reset(100);
                bforward(40,40);
                
                forward(90,40,40,MOTOR_C);
                
                angle(-680,100);
                bforward(0,80);
                reset(100);
                
                clock.wait(1000);
                break;
                
                /*
                 //手動
                 angle(680,100);
                 forward(290,80,0,0);
                 reset(100);
                 forward(150,40,40,1);
                 angle(-700,100);
                 forward(290,0,80,1);
                 reset(100);
                 clock.wait(10000);
                 */
            }
        }

    };
}