/* test_move*/
/*
メモ
motorAは+で右回り-で左回り
motorB,Cは-で直進
motorB = 左
motorC = 右

6/23
右旋回はほぼ完璧だが左旋回に少し難あり
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
int move(void);
//int screen(void);

TASK(TaskMain)
{
  Clock clock;
  Lcd lcd;

  int distance;
  int count0=0, count1=0, count2=0;
    
  motorA.reset();
  motorB.reset();
  motorC.reset();
  
  while(touch.isPressed()==0)
  {
    
    distance = sonar.getDistance();
    
    if(distance < 255){
        count0 = distance;
        if(count0 > count2){
            count2 = count0;
        }
        else if(count0 < count2){
            count1 = count0;
        }
        else{
        }
    }    
    if( distance < 20 ){
        if(count1+20 < count2){   
        move();
        }
    }
    else{
        motorB.setPWM(0);
        motorC.setPWM(0);
    }
    
     //各センサ・モータ類の値を常に画面に出力
    lcd.clear();   
    lcd.putf("sdn", "sonar:", distance,5);
    lcd.putf("sdn", "Rotation_A:", motorA.getCount(),0);
    lcd.putf("sdn", "Rotation_B:", motorB.getCount(),0);
    lcd.putf("sdn", "Rotation_C:", motorC.getCount(),0);
    lcd.putf("sdn", "touch: ", touch.isPressed(),5);
    lcd.putf("sdn", "gyro: ", gyro.getAnglerVelocity(),0);
    lcd.putf("sddn",  "1/2: ", count1,0,  count2,5);
    lcd.disp();

    //screen();
    clock.wait(150); //計測できる範囲を伸ばすため値を大きくしている。
  }
}


int move(void){
    while(motorB.getCount() > -720 && motorC.getCount() > -720){
            motorB.setPWM(-50);
            motorC.setPWM(-50);
            //screen();    
    }
    motorB.setPWM(0);
    motorC.setPWM(0);
    return 0;
}

/*
int screen(void){
    Lcd lcd;
    int distance = sonar.getDistance();
    lcd.clear();   
    //各センサ・モータ類の値を常に画面に出力
    lcd.putf("sdn", "sonar:", distance,5);
    lcd.putf("sdn", "Rotation_A:", motorA.getCount(),0);
    lcd.putf("sdn", "Rotation_B:", motorB.getCount(),0);
    lcd.putf("sdn", "Rotation_C:", motorC.getCount(),0);
    lcd.putf("sdn", "touch: ", touch.isPressed(),5);
    lcd.putf("sdn", "gyro: ", gyro.getAnglerVelocity(),0);
    lcd.putf("sddn",  "3/4: ", light.getBrightness(),0, sonar.getDistance(),5);
    lcd.disp();
}
*/

}
//end