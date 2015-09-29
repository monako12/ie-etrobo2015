/* sample.cpp for TOPPERS/ATK(OSEK) */

// ECRobot C++ API
#include "Clock.h"
#include "Lcd.h"
#include "Motor.h"
//#include "BTConnection.h"
//#include "Bluetooth.h"
#include "GyroSensor.h"
#include "LightSensor.h"
using namespace ecrobot;

extern "C"
{
/*#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    */
    
    class TwoBridge{
    
    public:
        
        Clock clock;
        Lcd lcd;
        
        //二本橋攻略
        int TwoBridge(int gyro_0){
            int gyro_1;
            int gyro_diff;
            
            //立つまでの処理
            motorB.setPWM(0);
            motorC.setPWM(0);
            
            while(motorB.getCount() > 100 && motorC.getCount() > 100){
                motorB.setPWM(30);
                motorC.setPWM(30);
            }
            
            while(motorB.getCount() > -100 && motorC.getCount() > -100){
                motorB.setPWM(-1000);
                motorC.setPWM(-1000);
            }
            
            motorB.setPWM(0);
            motorC.setPWM(0);
            
            while(ture){
                gyro_1 = gyro.getAnglerVelocity();
                gyro_diff = gyro_1 - gyro_0;
                
                //立ってからの処理
                motorB.setPWM(-10);
                motorC.setPWM(-10);
                
                if(gyro_diff > 80 && gyro_diff < 100){//坂に乗っている時の速度決定
                    motorB.setPWM(0);
                    motorC.setPWM(0);
                    
                    motorB.setPWM(100);
                    motorC.setPWM(100);
                }
            }
        }
        
        
        //難所検知
        void TwoBridgeDetection{
            int gyro_0;
            int gyro_1;
            int gyro_diff;
        
            gyro.setOffset(0);
            gyro_0 = gyro.getAnglerVelocity();
        
            while(true){
                gyro_1 = gyro.getAnglerVelocity();
                gyro_diff = gyro_1 - gyro_0;
          
                if(gyro_diff > 25){//衝突判定
                    //ここでクラスの読み込み
                    TwoBridge(gyro_0)
                }
            }
        }

        
    };
}
