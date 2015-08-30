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
class sensor{
	
	int sum;
	int white;
	int black;
	int gray;

public:
	int nowlight(int ava){
		int now;
		now = light.getBrightness();
		if(now > ava)
		{
			sum++;
		}else{
			sum--;
		}
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
		avarage = (white + black+100)/2;
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
		return(avarage);
	}

	int ret_sum(){
		return(sum);
	}
	int ret_white()
	{
		return(white);
	}
	int ret_black()
	{
		return(black);
	}
	int ret_gray()
	{
		return(gray);
	}
    int ret_avarage()
    {
        return(avarage);
    }
	
	void sonarwork(){}

	void gyrowork(){}
};

}