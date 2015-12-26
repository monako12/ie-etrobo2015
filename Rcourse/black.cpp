/* sample.cpp for TOPPERS/ATK(OSEK) */
//made by okada
// ECRobot C++ API
#include "Clock.h"
#include "calculation.cpp"
#include "sensor.cpp"
#include "drive.cpp"
#include "catch_gray.cpp"
#include "pid_run.cpp"
#include "barcode.cpp"
#include "train.cpp"
#include "parking.cpp"
#include "unknown.cpp"
#include "figurel.cpp"
#include "checkmotor.cpp"
#include "Nihonbashi.cpp"
#include "battery_test.cpp"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
//　タイヤの一周はgetCountでとると380ぐらいの値が出る.
// nxtOSEK hook to be invoked from an ISR in category 2
    void user_1ms_isr_type2(void)
    {
        SleeperMonitor();
    }

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        Cal cal;
        Barcode bar;
        Train train;
        Drive drive;
        Figurel fig;
	    Unknown unknown;
	    PIDrun pidrun;
        Nihonbashi nihonbashi;
	    Parking par;
	    CatchGray catchg;
	    Battery battery;

	    int i = 0;

	    /*while(1){ //main loop
	        pidrun.pid_running(false,0); //引数は1(leftEdge)か1以外(rightEdge)
	    }*/


			while(drive.position() > -1000){ //course R
				pidrun.pid_running(1,-10,20,30);
			}
			while(drive.position() > -5600){ //増えてるコメント消さないでください。byジャック
				pidrun.pid_dash_left();
			}
			while(drive.position() > -7600){
				pidrun.pid_running(3,-10,0,0);
			}
			while(drive.position() > -8500){
				pidrun.pid_running(1,-5,20,30);
			}
			while(drive.position() > -11000){
				pidrun.pid_running(3,-15,0,0);
			}
			while(drive.position() > -12500){
				pidrun.pid_dash_left();
			}
			while(drive.position() > -14100){
				pidrun.pid_running(3,-10,0,0);
			}
			drive.motor_stop();
			clock.wait(2000);
	  	  	fig.figurel();
	        train.train();

	        while(5000 > i){
	        	i++;
	        	pidrun.pid_running(2,-15,0,0);
	        }

	        drive.motor_count_reset();
	        while(drive.position() > -600){ //course R
				pidrun.pid_running(2,-10,0,0);
			}
			while(drive.position() > -1450){ //増えてるコメント消さないでください。byジャック
				pidrun.pid_dash();
			}
			while(drive.position() > -3700){
				pidrun.pid_running(2,-10,0,0);
			}
			while(drive.position() > -8520){
				pidrun.pid_dash();
			}
			
	        motorA.setPWM(0);
	        motorB.setPWM(0);
	        motorC.setPWM(0);
	        par.shin_parallel_parking();
            while(1){
            pidrun.pid_running(2,0,0,0);
            }


	        //clock.wait(100000);

			//pidrun.pid_running(1,0);
            //pidrun.gray_discover();

            //train.train();
		
    }
}
