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
	
	

	void motora(int pid,int line)
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
		int b;
		int c;
		if(pid > 0)
		{
			b = -35 - (pid/4);
			c = -35 + (pid/4);
		}else
		{
			b = -35 + (pid/4);
			c = -35 - (pid/4);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);


	}
	void motorb(int pow)
	{


	}

	void motorc(int pow)
	{

	}
	
	void mode_out(int pid,int line)
	{

		if(line > 0)
		{
			
			if(motorA.getCount() < 150)
			{
				motorA.setPWM(100);
			}else{
				motorA.setPWM(0);
			}
		}
		if(line < 0)
		{
			
			if(motorA.getCount() > -150){

				motorA.setPWM(-100);
			}else{
				motorA.setPWM(0);
			}


		}
		int b;
		int c;
		if(pid > 0)
		{
			b = -35 - (pid/3);
			c = -35 + (pid/4);
		}else
		{
			b = -35 + (pid/4);
			c = -35 - (pid/3);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);


	}
	void mo(int pid,int line,int sum)
	{
		if(sum == 0)
		{
			motora(pid,line);

		}
		if(sum == 1)
		{
			mode_out(pid,line);
		}

		

	}


}
