//made by okada
#include "Motor.h"
#include "math.h"
#include "stdlib.h"

using namespace ecrobot;
extern "C"
{

	Motor motorA(PORT_A);
	Motor motorB(PORT_B);
	Motor motorC(PORT_C);
	Clock clock;
	class Drive{

	public:
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

	void motorb(int pow)
	{


	}

	void motorc(int pow)
	{

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

	  void mode_Black_Left(int pid,int line)
	  {
	    if(line < 0)
	      {
		if(motorA.getCount() <= 200)
		  {
		    motorA.setPWM(100);
		  }else{
		  motorA.setPWM(0);
		}
	      }
	    if(line > 0)
	      {
		
		if(motorA.getCount() >= -200){
		  
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
		b = -30 + (pid/3);
		c = -40 - (pid/4);
	      }
	    
	    motorC.setPWM(c);
	    motorB.setPWM(b);
	    
	  }
	  void mode_Black_Right(int pid,int line){
	    if(line < 0)
	      {
		if(motorA.getCount() >= -200)
		  {
		    motorA.setPWM(-100);
		  }else{
		  motorA.setPWM(0);
		}
	      }
	    if(line > 0)
	      {
		
		if(motorA.getCount() <= 200){
		  
		  motorA.setPWM(100);
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
		b = -37 - (pid/4);
		c = -37 + (pid/4);
	      }
	    
	    motorC.setPWM(c);
	    motorB.setPWM(b);
	    
	  }

	int seto()
	{
		
		while(1)
		{
			int va = motorA.getCount();
			motorB.setPWM(0);
			motorC.setPWM(0);
			if(va < 2)
			{
				motorA.setPWM(50);
			}
			if(va > 2)
			{
				motorA.setPWM(-50);
			}
			if(va == 0)
			{
				motorA.setPWM(0);
				motorC.setPWM(20);
				motorB.setPWM(20);
				return(0);
			}
			
		clock.wait(1);

		}
	}
};

}
