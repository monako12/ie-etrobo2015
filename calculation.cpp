#include "Lcd.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
	double p_coe = 0.34;
	double i_coe = 0.34;
	double d_coe = 0.34;
	int a = 1;
	double p_i_d(int ava,double cur)
	{
		

		double p;
		double i;
		double d;
		double delta_t = 2;
		double diff[3];
		double integral = 0;
		double cur2;
		diff[0] = diff[1];
		diff[1] = cur - ava;
		integral += (diff[1] + diff[0])/2*delta_t;
		p = p_coe*diff[1];
		i = i_coe*integral;
		d = d_coe*(diff[1]-diff[0])/delta_t;
		if(a == 1) {
			cur = p + i + d;
		}else {
			cur = p / 2 + i + d;
		}
		return (int)cur;
	}


}
