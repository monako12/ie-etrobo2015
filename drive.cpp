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
	
	int Acount()
	{
		return(motorA.getCount());
	}

	int Bcount()
	{
		return(motorB.getCount());
	}

	int Ccount()
	{
		return(motorC.getCount());
	}

	void motora(int pid,int line)
	{	
		if(line < 0)
		{
			if(motorA.getCount() < 200)
			{
				motorA.setPWM(100);
			}else{
				motorA.setPWM(0);
			}
		}
		if(line > 0)
		{
			if(motorA.getCount() > -200){

				motorA.setPWM(-100);
			}else{
				motorA.setPWM(0);
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
		if(pid < 0)
		{
			b = -35 + (pid/4);
			c = -35 - (pid/4);
		}else
		{
			b = -35 - (pid/4);
			c = -35 + (pid/4);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);
	}
	void curve(int sum,int line){

		if(sum > 100){

			if(line < 0)
			{
				if(motorA.getCount() < 200)
				{
					motorA.setPWM(50);
				}else{
					motorA.setPWM(0);
				}
			}
			if(line > 0)
			{
				if(motorA.getCount() > -200){

					motorA.setPWM(-50);
				}else{
					motorA.setPWM(0);
				}

			}

		}

	}
	void mode_in()
	{
		if(line < 0)
		{
			if(motorA.getCount() < 200)
			{
				motorA.setPWM(100);
			}else{
				motorA.setPWM(0);
			}
		}
		if(line > 0)
		{
			if(motorA.getCount() > -200){

				motorA.setPWM(-100);
			}else{
				motorA.setPWM(0);
			}


		}
		int b;
		int c;
		if(pid < 0)
		{
			b = -35 + (pid/4);
			c = -35 - (pid/4);
		}else
		{
			b = -35 - (pid/4);
			c = -35 + (pid/4);
		}

		motorC.setPWM(c);
		motorB.setPWM(b);

	}
	void mode_out(int pid,int line)
	{

		if(line > 0)
		{
			if(motorA.getCount() < 200)
			{
				motorA.setPWM(100);
			}else{
				motorA.setPWM(0);
			}
		}
		if(line < 0)
		{
			if(motorA.getCount() > -200){

				motorA.setPWM(-100);
			}else{
				motorA.setPWM(0);
			}


		}
		int b;
		int c;
		if(pid < 0)
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

}