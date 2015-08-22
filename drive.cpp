#include "Motor.h"
#include "math.h"
#include "Lcd.h"
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
	Lcd lcd;
	
	

	void motora(int pid)
	{	
		int a;
		a = abs(motorA.getCount());
		if (a < 100 || (0 > pid * motorA.getCount()))
		{

			motorA.setPWM(pid/5);

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
		b = 50 + pid;
		c = 50 - pid;
		motorC.setPWM(c);
		motorB.setPWM(b);
	}
}