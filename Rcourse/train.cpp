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
 /*
 PID
 第1引数 右(0,2)or左(1,3) *今まで(電池80%時ぐらい)のpidなら、2or3で、第2引数を-10 (2,)
 第2引数 3固定(左トレース) *2or3のみ設定。スピード調整用の引数。0or1の場合、0でok
 第3引数 前輪の角度 *0or1のみ設定。2or3の場合、0でok
 第4引数 前輪のスピード *上記
 意味不明
 */
//10/2完成
// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "Clock.h"
#include "Lcd.h"

#include "Motor.h"

using namespace ecrobot;


extern "C"
{

    class Train{

    public:

        Clock clock;
        Lcd lcd;
        Drive drive;
        Barcode bar;

        void reset(int speed){//parkingから引用
        int nrotate;
            while(1){
                nrotate = motorA.getCount();
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

        void Ride_bord_train(int time){
            int velocity;
            int borderline;
            int diff_gyro;
            bool flag = false;

            gyro_bar.setOffset(0);
            motorA.setPWM(0);
            motorB.setPWM(-20);
            motorC.setPWM(-20);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;
                lcd.clear();
                if(flag){
                    motorB.setPWM(0);
                    motorC.setPWM(0);
                    lcd.putf("sn","hoge");
                    lcd.putf("sdn","diff:",diff_gyro,0);
                    lcd.putf("sdn","border:",borderline,0);
                    lcd.putf("sdn","now:",velocity,0);
                    lcd.disp();
                    clocktime.wait(800);
                    break;
                }
                if(diff_gyro > BORDER){
                    motorC.setPWM(0);
                    motorB.setPWM(0);
                    clock.wait(500);

                    motorA.setPWM(-20);
                    motorC.setPWM(-60);
                    motorB.setPWM(-60);
                    clocktime.wait(time);
                    flag = true;
                }
                lcd.putf("sdn","diff:",diff_gyro,0);
                lcd.disp();
                clocktime.wait(5);
            }
        }

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

    void A_set(){
        motorA.setPWM(90);
        clock.wait(400);
        motorA.setPWM(-90);
        clock.wait(600);
        reset(100);
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
        //pidrun.pid_running(1,-10,20,30);
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
        pidrun.pid_running(2,-10,0,0);
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

    void train()
    {
        int distance;
        int measure0=0, measure1=0, measure2=0;
        int count=1;
        int deg;
        bool flag=true;

        motorA.reset();
        motorB.reset();
        motorC.reset();

        clock.sleep(100);

        while(flag == true)
        {

            distance = sonar.getDistance();

            switch(count){
                case 1:
                    if(distance < 120){///--------------要注意!!!!!!!!本番では150~200
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
                        if(measure1+30 < measure2){//30
                            clock.sleep(1200);
                            //move_pid(measure1-20,false);
                            move_pid_slow(measure1-17);
                            A_set();
                            count++;
                        }
                    }
                    break;
                case 2:
                    if(distance < 25){//変えるべき? 10/2 100
                        clock.sleep(1200);
                        //reset(100);
                        //bar.ride_bord(200);
                        Ride_bord_train(400);
                        //move_pid(measure2-measure1-23,false);//-10
                        move_pid_slow(measure2-measure1-10);
                        A_set();
                        count++;
                    }
                    //reset(100);
                    break;
                case 3:
                    if(distance < 100){
                        clock.sleep(1200);
                        move_pid_slow(20);//measure2-measure1-10
                        //move_pid(measure2-measure1-10,false);
                        count++;
                    }
                    reset(100);
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

            clock.wait(100); //計測できる範囲を伸ばすため値を大きくしている。
        }
    }

};

}
//end:
