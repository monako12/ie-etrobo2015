/* test_move*/
/*
 メモ
 9/1
 motorAは+で右回り-で左回り
 motorB,Cは-で直進
 motorB = 左
 motorC = 右
 タイヤの半径は約4cm
 円周率 = 3 を使用
 タイヤ一回転(360°)での移動距離は約24cm
 */

// ECRobot++ API
#include "LightSensor.h"
#include "SonarSensor.h"
#include "SoundSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "Clock.h"
#include "Lcd.h"

#include "Motor.h"
#include "Nxt.h"

using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    
    LightSensor  light(PORT_3);
    SonarSensor  sonar(PORT_4);
    GyroSensor   gyro(PORT_1);
    TouchSensor  touch(PORT_2);
    
    Motor       motorA(PORT_A);
    Motor       motorB(PORT_B);
    Motor       motorC(PORT_C);
    
    /* nxtOSEK hook to be invoked from an ISR in category 2 */
    void user_1ms_isr_type2(void)
    {
        SleeperMonitor(); // needed for I2C device and Clock classes
    }
    
    //関数 プロトタイプ宣言
    int move(int);
    int moving_distance(int n1 ,int n2);
    
    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        
        int distance;
        int measure0=0, measure1=0, measure2=0;
        int count=1;
        int deg;
        
        motorA.reset();
        motorB.reset();
        motorC.reset();
        
        while(touch.isPressed()==0)
        {
            
            distance = sonar.getDistance();
            
            switch(count){
                case 1:
                    if(distance < 255){
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
                    /*if( distance < 20 ){
                     if(measure1+20 < measure2){
                     move(moving_distance(measure1 ,measure2));
                     count++;
                     }
                     }
                     else{
                     motorB.setPWM(0);
                     motorC.setPWM(0);
                     */
                    if(measure1 != 0){
                        if(measure1+20 < measure2){
                            move((measure1*360)/(8*3));
                            count++;
                        }
                    }
                    break;
                case 2:
                    /*if( distance < 30){
                     move(720);  //ここの値は適当
                     }*/
                    if(distance < 20){
                        if(distance > 250){
                            move(measure2 - measure1);
                        }
                    }
                    count++;
                    break;
                case 3:
                    if(distance < 20){
                        if(distance > 250){
                            move(500);
                        }
                    }
                    break;
                default:
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
    
    int move(int distance)
    while(motorB.getCount() > -distance && motorC.getCount() > -distance){
        motorB.setPWM(-50);
        motorC.setPWM(-50);
    }
    motorB.setPWM(0);
    motorC.setPWM(0);
    motorB.reset();
    motorC.reset();
    
    return 0;
}


int moving_distance(int m1 ,int m2){
    int deg;
    int distance;
    int pi = 3; //円周率
    int r = 4; //後輪の半径
    
    motorB.reset();
    motorC.reset();
    
    distance = m2 - m1;
    deg = (distance*360) / (2*pi*r);
    
    return deg;
}

}
//end:

