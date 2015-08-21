#include "Motor.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
	Motor motorA(PORT_A);
	Motor motorB(PORT_B);
	Motor motorC(PORT_C);

	void motora(int black)
	{
 motorA.setPWM(black);
	}

	void motorb()
	{


	}

	void motorc()
	{

	}
}