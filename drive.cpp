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

  int position()
  {
    return((Bcount()+Ccount())/2);
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
        motorA.setPWM(80);
      }else{
      motorA.setPWM(0);
    }
        }
      if(line > 0)
        {

    if(motorA.getCount() >= -200){
      motorA.setPWM(-80);
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
        motorA.setPWM(-80);
      }else{
      motorA.setPWM(0);
    }
        }
      if(line > 0)
        {

    if(motorA.getCount() <= 200){

      motorA.setPWM(80);
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
        }else{
    b = -37 - (pid/4);
    c = -37 + (pid/4);
        }

      motorC.setPWM(c);
      motorB.setPWM(b);

    }

	int dash(int pid,int line){
		if(line < 0)
		{
			if(motorA.getCount() <= -40)
			{
				motorA.setPWM(-25);
			}else
			{
				motorA.setPWM(0);
			}
		}
		if(line > 0)
		{
			if(motorA.getCount() >= 40)
			{
				motorA.setPWM(25);
				}else
				{
					motorA.setPWM(0);
					{
				}
			}
		}
		int b;
		int c;
		if(pid < 0)
		{
			b = -85 + (pid/4);
			c = -85 - (pid/4);
		}else
		{
			b = -79 + (pid/3);
			c = -92 - (pid/4);
		}
		motorC.setPWM(c);
		motorB.setPWM(b);
	}

	int fix_position(int pid,int line){
		int b;
		int c;
		int fix_distance;
		while(1){
		  motorB.reset();
		  motorC.reset();
		  if(line > 0){  //-------------------------
		    if(motorA.getCount() >= -80){
		      motorA.setPWM(-60);
		    }else{
		      motorA.setPWM(0);
		    }
		    b = -30 + (pid/3);
		    c = -40 - (pid/4);
		    motorC.setPWM(c);
		    motorB.setPWM(b);
		    fix_distance = position();
		  }else{
		    //if(fix_distance == )
		    motorB.reset();
		    motorC.reset();
		    while(position()<40){
		      back();
		    }
		    motorB.setPWM(0);
		    motorC.setPWM(0);
		    break;
		  }
		}
		motorB.reset();
		motorC.reset();
	}

    void back(){
      if(motorA.getCount() >= -600){
	motorA.setPWM(-100);
      }else{
	motorA.setPWM(0);
	motorC.setPWM(60);
	motorB.setPWM(-40);
      }      
    }
/*  int seto()
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
  }*/
};

}
