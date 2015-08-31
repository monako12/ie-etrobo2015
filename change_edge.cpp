//made by okada
#include "stdlib.h"
using namespace ecrobot;
extern "C"
{

int count_B;
int count_C;
Drive drive;


	

	
	int motorcount(int pid, int line)
	{
		/*
		if(-400 < count_B && count_B < -20)
		{
			mode_in(pid,line);
			

		}if (-549 < count_B && count_B < -401)
		{
			seto();
			/ code /
		}
		if(-800 < count_B && count_B < -550)
		{
			mode_out(pid,line);
			
		}
		*/
		//drive.mode_Black_Left(pid,line);
	  drive.mode_Black_Right(pid, line);
		//curve(pid,line);






	}
	int change_edge(int pid,int line)
	{	int a = 0;
		int b = 0;

		count_B = drive.Bcount();
		count_C = drive.Ccount();
		motorcount(pid,line);
		


		}
}
