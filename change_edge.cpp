#include "stdlib.h"
#include "drive.cpp"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
int count_B;
int count_C;
	int change_edge(int pid,int line)
	{	int a;
		int b;

		count_B = Bcount();
		count_C = Ccount();
		switch(a < count_B && count_B < b)
		{

			case (a == 20 && b == 200):
			edge_inpre();
			edge_in(pid,line);
			break;

			case (a == 220 && b == 400):
			edge_outpre();
			edge_out();
			break;

			default:
			break;





		}

	

	}