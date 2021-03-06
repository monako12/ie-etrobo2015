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
	    /*while(1){ //main loop
	        pidrun.pid_running(false,0); //引数は1(leftEdge)か1以外(rightEdge)
	    }*/
/*			while(drive.position() > -900){ //course R
				pidrun.pid_running(1,0);
			}
			while(drive.position() > -5600){ //増えてるコメント消さないでください。byジャック
				pidrun.pid_dash_left();
			}
			while(drive.position() > -12200){
				pidrun.pid_running(1,0);
			}
			bool huga = false;
			while(huga == false){
				pidrun.pid_running(3,-17);
				huga = pidrun.gray_discover();
			}*/


			while(drive.position() > -900){ //course L
				pidrun.pid_running(2,-10,5,50);
			}
			while(drive.position() > -6500){
				pidrun.pid_dash();
			}
			while(drive.position() > -8800){
				pidrun.pid_running(2,-10,0,0);
			}
			while(drive.position() > -9900){
				pidrun.pid_running(2,-10,0,0);
			}

			nihonbashi.stop_ex();
			train.move_pid4(60);
			train.move_pid2(40);
			bar.barcode(sen.ret_white(),sen.ret_black());
			unknown.Capture_unknown(bar.array);
            drive.motor_count_reset();
            drive.motor_stop();
            while(drive.position() > -1900){
            	pidrun.pid_running(2,-10,0,0);
            }
            while(drive.position() > -9200){
            pidrun.pid_dash();
            }
            drive.motor_stop();
            par.shin_right_angle_parking();
            while(1){
            pidrun.pid_running(0,0,200,70);
            }



	   /* while(1){ //test loop
	        //If you do test program,you have to write in this while loop.
	    		   //figurelから新幹線

	  	  	  	   fig.figurel();
	               train.train();

	               while(1){
	            	   pidrun.pid_running(0,0,200,70);
	               }
	               clock.wait(100000);

					//pidrun.pid_running(0,0,350,80);
					//pidrun.gray_discover();
		}*/
    }
}
