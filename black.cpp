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
			/*while(drive.position() > -5500){ //増えてるコメント消さないでください。byジャック
				pidrun.pid_dash_left();
			}
			while(drive.position() > -12000){
				pidrun.pid_running(1,0);
			}*/
	    while(1){ //test loop
	        //If you do test program,you have to write in this while loop.
					//pidrun.pid_running(3,-10);
					//pidrun.gray_discover();
		}
    }
}
