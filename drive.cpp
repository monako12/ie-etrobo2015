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
			b = -15 - (pid/8);
			c = -15;
		}else
		{
			b = -15;
			c = -15 - (pid/8);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);
	}
}