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

	void motora()
	{
 motorA.setPWM(20);
	}

	void motorb()
	{


	}

	void motorc()
	{

	}
}