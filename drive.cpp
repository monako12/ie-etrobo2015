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
	
	

	void motora(int ava)
	{	
		
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
			b = -70 - (pid/2);
			c = -70 + (pid/2);
		}else
		{
			b = -70 + (pid/2);
			c = -70 - (pid/2);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);
	}
}