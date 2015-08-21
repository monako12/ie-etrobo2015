#include "LightSensor.h"
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"
#include "Lcd.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#include "Clock.h"

	LightSensor  light(PORT_3,true);
	SonarSensor  sonar(PORT_4);
	GyroSensor   gyro(PORT_1);
	TouchSensor  touch(PORT_2);
    TouchSensor  touchwhite(PORT_2);
	TouchSensor  touchblack(PORT_2);

	int nowlight(){
		int now;
		now = light.getBrightness();
		return(now);
	}

	int lightavarage(){
		Clock clock;
		
		Lcd lcd;
		int white = 11000010;
		int black;
		int avarage;
		lcd.clear();
		
		while(touchwhite.isPressed()==0)
		{

			white = light.getBrightness();
			lcd.putf("sdn", "white:", white,0);
			clock.wait(2000);
		}
		while(touchblack.isPressed()==0)
		{

			black = light.getBrightness();
			lcd.putf("sdn", "black:", black,0);
			clock.wait(2000);
		}
		avarage = (white + black)/2;
		return(avarage);
	}

	void sonarwork(){}

	void gyrowork(){}

}