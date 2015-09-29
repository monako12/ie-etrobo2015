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

        Cal cal;
        PIDrun pidrun;

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

        void right_angle_parking()
        {
            while(1)
            {

                reset(100);
                srotate = nxt_motor_get_count(PORT_C);
                while(1){
                    nrotate = nxt_motor_get_count(PORT_C);
                    if (nrotate > (srotate + ((-1) * 1300))){
                        pidrun.pid_running(false,0);
                    }
                    else {
                        break;
                    }
                }

                motorB.setPWM(0);
                motorC.setPWM(0);

                reset(100);

                //前輪角度
                drive.angle(-700,100);
                //回転
                drive.forward(295,0,80,MOTOR_C);

                //角度直し
                reset(100);
                //バック
                drive.forward(-780,40,40,MOTOR_C);
                clock.wait(5000);

                drive.bforward(40,40);
                drive.forward(130,40,40,MOTOR_C);

                drive.angle(680,100);
                drive.bforward(80,0);
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

                //forward(1400,40,40,MOTOR_C);
                srotate = nxt_motor_get_count(PORT_C);
                while(1){
                    nrotate = nxt_motor_get_count(PORT_C);
                    if (nrotate > (srotate + ((-1) * 1400))){
                        pidrun.pid_running(false,0);
                    }
                    else {
                        break;
                    }
                }
                motorB.setPWM(0);
                motorC.setPWM(0);
                reset(100);

                drive.angle(350,100);
                drive.forward(310,40,40,MOTOR_C);
                reset(100);

                drive.forward(-820,40,40,MOTOR_C);

                drive.angle(-650,100);
                drive.forward(100,0,70,MOTOR_C);
                reset(100);

                clock.wait(5000);


                //sensor
                drive.angle(680,100);
                drive.forward(290,80,0,MOTOR_B);
                reset(100);
                drive.bforward(40,40);

                drive.forward(90,40,40,MOTOR_C);

                drive.angle(-680,100);
                drive.bforward(0,80);
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
