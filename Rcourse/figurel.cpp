using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define MOTOR_B 0
#define MOTOR_C 1

class Figurel{
    public:
        int srotate;
        int nrotate;

        Cal cal;
        Drive drive;
        SensorGet sen;
        Parking par;

        void figurel()
        {
            clock.wait(2000);
            bar.L_ride_bord(true);
            while(true){
            	set_rotate_pid(350,3,-10);
                L_carve();
                clock.wait(1000);
                set_rotate_pid(500,2,-15);
                drive.motor_stop();
                par.reset(100);
                break;
            }
        }

        void set_rotate_pid(int rotate,int side,int speed){
        	srotate = nxt_motor_get_count(PORT_C);
        	while(1){
        		nrotate = nxt_motor_get_count(PORT_C);
        		if (nrotate > (srotate + ((-1) * rotate))){
        			pidrun.pid_running(side,speed,0,0);
        		} else {
        			break;
        		}
        	}
        }

        void L_carve(){
        	motorB.setPWM(0);
        	motorC.setPWM(0);
        	par.reset(100);
        	drive.angle(380,100);
        	drive.lforward(100,70,70,MOTOR_C);
        	drive.bforward(70,70);
        	drive.angle(-100,100);
        	drive.forward(50,50,50,MOTOR_C);
        	drive.angle(400,80);
        	drive.lbforward(50,0);
        	drive.forward(40,50,0,MOTOR_B);
        	par.reset(100);
        }
    };
}
