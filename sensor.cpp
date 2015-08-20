#include "LightSensor.h"
#include "SonarSensor.h"
#include "SoundSensor.h"
#include "TouchSensor.h"
#include "GyroSensor.h"

using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

LightSensor  light(PORT_3/* lamp off */);
	SonarSensor  sonar(PORT_4);
	GyroSensor   gyro(PORT_1);
	TouchSensor  touch(PORT_2);


	int nowlight(){
		int now;
		now = light.getBrightness();
		return(now);
	}

	int lightavarage(){
		TouchSensor  touchwhite(PORT_2);
		TouchSensor  touchblack(PORT_2);
		int white;
		int black;
		int avarage;
		while(touchwhite.isPressed() == 0)
		{

			white = light.getBrightness();

		}
		while(touchblack.isPressed() == 0)
		{

			black = light.getBrightness();

		}
		avarage = (white + black)/2;
		return(avarage);
	}

	void sonarwork(){}

	void gyrowork(){}

}