/* test_move*/
/*
 メモ
 9/18　完成 たぶん....
 motorAは+で右回り-で左回り
 motorB,Cは-で直進
 motorB = 左
 motorC = 右
 タイヤの半径は約4cm
 円周率 = 3 を使用
 タイヤ一回転(360°)での移動距離は約24cm
 */
//9/30
// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "Clock.h"
#include "Lcd.h"

#include "Motor.h"w

using namespace ecrobot;

extern "C"
{

    //Drive drive;

    class Train{

    public:

        Clock clock;
        Lcd lcd;
        Drive drive;

        int move(int distance){
            if(distance>0){//前進
                while(motorB.getCount() > -distance && motorC.getCount() > -distance){
                    motorB.setPWM(-50);
                    motorC.setPWM(-50);
                }
            }
            else{//後退
                while(motorB.getCount() < -distance && motorC.getCount() < -distance){
                    motorB.setPWM(50);
                    motorC.setPWM(50);
                }
            }
            motorB.setPWM(0);
            motorC.setPWM(0);
            motorB.reset();
            motorC.reset();

            return 0;
        }

    void move_pid(int distance, bool flag){
        int deg;
        deg = moving_distance(distance);
        while(true) {
            if(drive.position()<-deg){
                drive.motor_stop();
            break;
            }
        pidrun.pid_running(0,0,20,30);
        }

    }
    void move_pid2(int distance){
        int deg;

        deg = moving_distance(distance);
        while(true) {
            if(drive.position()<-deg){
                drive.motor_stop();
            break;
            }
        pidrun.pid_running(0,-20,300,50);
        }
    }

    void move_pid3(int distance, bool flag){
        int deg;
        deg = moving_distance(distance);
        while(true) {
            if(drive.position()<-deg){
                drive.motor_stop();
            break;
            }
        pidrun.pid_running(1,0,350,80);
        }

    }

    void move_pid_slow(int distance){
        int deg;

        deg = moving_distance(distance);
        while(true) {
            if(drive.position()<-deg){
                drive.motor_stop();
            break;
            }
        pidrun.pid_running(2,0,0,0);
        }
    }

    int moving_distance(int distance){
        int deg;
        int pi = 3; //円周率
        int r = 4; //後輪の半径

        motorB.reset();
        motorC.reset();

        deg = (distance*360) / (2*pi*r);//要値調整

        return deg;
    }

    void Motor_reset(){
        motorA.reset();
        motorB.reset();
        motorC.reset();
    }

    void train()
    {
        int distance;
        int measure0=0, measure1=0, measure2=0;
        int count=1;
        int deg;
        bool flag=true;

        Motor_reset();

        while(flag == true)
        {

            distance = sonar.getDistance();

            switch(count){
                case 1:
                    if(distance < 230){//255
                        measure0 = distance;
                        if(measure0 > measure2){
                            measure2 = measure0;
                        }
                        else if(measure0 < measure2){
                            measure1 = measure0;
                        }
                        else{
                        }
                    }
                    if(measure1 != 0){
                        if(measure1+30 < measure2){
                            clock.sleep(1200);
                            deg = moving_distance(measure1-20);
                            while(true) {
                                if(drive.position()<-deg){
                                drive.motor_stop();
                                break;
                                }
                                pidrun.pid_running(false,0,80,350);
                            }
                            count++;
                        }
                    }
                    break;
                case 2:
                    if(distance < 100){
                        clock.sleep(1200);
                        deg = moving_distance(measure2-measure1-10);
                        while(true) {
                            if(drive.position()<-deg){
                                drive.motor_stop();
                                break;
                            }
                            pidrun.pid_running(false,0,80,350);
                        }
                        count++;

                    }
                    break;
                case 3:
                    if(distance < 100){
                        clock.sleep(1200);
                        deg = moving_distance(measure2-measure1-10);
                        while(true) {
                            if(drive.position()<-deg){
                                drive.motor_stop();
                                break;
                            }
                            pidrun.pid_running(false,0,350,80);
                        }
                        count++;
                    }
                    break;
                case 4:
                    flag=false;
                    break;
                default:
                    flag=false;
                    motorB.setPWM(0);
                    motorC.setPWM(0);
                    break;

            }

            //各センサ・モータ類の値を常に画面に出力

            lcd.clear();
            lcd.putf("sdn", "count", count,0);
            lcd.putf("sdn", "Rotation_A:", motorA.getCount(),0);
            lcd.putf("sdn", "Rotation_B:", motorB.getCount(),0);
            lcd.putf("sdn", "Rotation_C:", motorC.getCount(),0);
            lcd.putf("sdn", "touch: ", touch.isPressed(),5);
            lcd.putf("sdn", "gyro: ", gyro.getAnglerVelocity(),0);
            lcd.putf("sddn",  "1/2: ", measure1,0,  measure2,5);
            lcd.disp();

            clock.wait(150); //計測できる範囲を伸ばすため値を大きくしている。
        }
    }

};

}
//end:
