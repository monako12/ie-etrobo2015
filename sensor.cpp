//made by okada
#include "LightSensor.h"
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
	LightSensor  light(PORT_3,true);
	SonarSensor  sonar(PORT_4);
	GyroSensor   gyro(PORT_1);
	TouchSensor  touch(PORT_2);
	TouchSensor  touchwhite(PORT_2);
	TouchSensor  touchblack(PORT_2);
    int avarage;
class SensorGet{

  int white;
  int black;
  int gray;
  int Threshold;
  int g_Threshold;

public:
  int nowlight(){
    int now;
    now = light.getBrightness();
    return(now);
  }

  int lightavarage(){
    Clock clock;
    Lcd lcd;
    lcd.clear();

    while(touch.isPressed()==0)
      {
      }
    white = light.getBrightness();
    lcd.putf("sdn", "white:", white,0);
    lcd.disp();
    while(touchblack.isPressed()==1)
      {
      }
    black = light.getBrightness();
    lcd.putf("sdn", "black:", black,4);
    lcd.disp();
    avarage = (white + black)/2;
    while(touch.isPressed()==0)
      {
      }
    gray = light.getBrightness();
    lcd.putf("sdn", "gray:", gray,0);
    lcd.disp();
    while(touch.isPressed()==1)
      {
      }
    while(touch.isPressed()==0)
      {
      }
    if(avarage < gray){
      Threshold = gray + 15;
	  g_Threshold = avarage;
    }else{
      Threshold = gray + 20;
	  g_Threshold = avarage;
    }
    return(0);
  }

  int ret_white(){
    return(white);
  }
  int ret_black(){
    return(black);
  }
  int ret_gray(){
    return(gray);
  }
  int ret_Threshold(){
    return(Threshold);
  }
  int ret_grayThreshold(){
	  return(g_Threshold);
  }
  int ret_avarage(){
    return(avarage);
  }
  int sonarwork(){
    return(sonar.getDistance());
  }
  void gyrowork(){}
};

}
