#include "Motor.h"
#include "math.h"
#include "stdlib.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
	Motor motorA(PORT_A);
	Motor motorB(PORT_B);
	Motor motorC(PORT_C);
	int sum;
	
	

	void motora(int pid)
	{	
		if(pid < 0)
		{
			motorA.setPWM(0);
		}
		else
		{
			motorA.setPWM(0);

		}
	}
	void motorb(int pow)
	{


	}

	void motorc(int pow)
	{

	}
	void motorbc(int pid)
	{
		int b;
		int c;
		if(pid < 0)
		{
			b = pid/2 - pid/7;
			c = pid/2 ;
		}else
		{
			b = pid/2;
			c = pid/2 - pid/7;
		}

		motorC.setPWM(-60 + (abs(c)));
		motorB.setPWM(-60 + (abs(b)));
	}
}