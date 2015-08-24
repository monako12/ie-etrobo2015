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
			motorA.setPWM(-100);
		}
		else
		{
			motorA.setPWM(100);

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
			b = -25 - (pid/7);
			c = -25;
		}else
		{
			b = -25;
			c = -25 - (pid/7);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);
	}
}