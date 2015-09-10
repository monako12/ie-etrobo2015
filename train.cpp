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

using namespace ecrobot;

extern "C"
{
    
    class Train{
        
    public:
        
        Clock clock;
        Lcd lcd;
        
        int move(int distance){
            if(flag = 0){
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
            else if(flag = 1){
                //ライントレースで走る部分
                while(motorB.getCount() > -distance && motorC.getCount() > -distance){
                    pidrun.pid_running(false);
                }
                motorB.setPWM(0);
                motorC.setPWM(0);
                motorB.reset();
                motorC.reset();
            
                return 0;
            }
        }
    
        
        int moving_distance(int distance){
            int deg;
            int pi = 3; //円周率
            int r = 4; //後輪の半径
            
            motorB.reset();
            motorC.reset();
            
            deg = (distance*360) / (2*pi*r)-20;
            
            return deg;
        }
        
        void train()
        {
           
            
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
                        if(measure1 != 0){
                            if(measure1+20 < measure2){
                                clock.sleep(1200);
                                move(moving_distance(measure1),1);//ライントレース
                                count++;
                            }
                        }
                        break;
                    case 2:
                        if(distance < 20){
                            count++;
                        }
                        break;
                    case 3:
                        if(distance >250){
                            clock.sleep(1200);
                            move(moving_distance(measure2-measure1),0);
                            move(200,1);//ライントレース
                            count++;
                        }
                        break;
                    case 4:
                        if(distance < 20){
                            count++;
                        }
                        break;
                    case 5:
                        if(distance > 250){
                            clock.sleep(1200);
                            move(500,0);
                            move(500,1);//ライントレース
                            count++;
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
        
    };
    
}
//end:


