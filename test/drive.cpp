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
	
	

	void motora(int pid,int line,int sum)
	{	if(sum == 1)
		{
			if(line < 0)
			{
				if(motorA.getCount() < 90)
				{
					motorA.setPWM(100);
				}else{
					motorA.setPWM(0);
				}
			}
			if(line == 0)
			{
				if(motorA.getCount() > -90){

					motorA.setPWM(-100);
				}else{
					motorA.setPWM(0);
				}


			}
		}else
		{
			if(line > 0)
			{
				if(motorA.getCount() < 90)
				{
					motorA.setPWM(100);
				}else{
					motorA.setPWM(0);
				}
			}
			if(line < 0)
			{
				if(motorA.getCount() > -90){

					motorA.setPWM(-100);
				}else{
					motorA.setPWM(0);
				}
			}

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
		if(pid > 0)
		{
			b = -35 + (pid/3);
			c = -35 - (pid/3);
		}else
		{
			b = -35 - (pid/3);
			c = -35 + (pid/3);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);
	}
	void curve(int sum,int line){

		if(sum == 300){

			if(line < 0)
			{
				if(motorA.getCount() < 200)
				{
					motorA.setPWM(100);
				}else{
					motorA.setPWM(0);
				}
			}
			if(line == 0)
			{
				if(motorA.getCount() > -200){

					motorA.setPWM(-100);
				}else{
					motorA.setPWM(0);
				}

			}
		}


	}

}
