/* sample.cpp for TOPPERS/ATK(OSEK) */
//made by okada
// ECRobot C++ API
#include "Clock.h"
#include "calculation.cpp"
#include "sensor.cpp"
#include "drive.cpp"
#include "pid_run.cpp"
#include "barcode.cpp"
#include "train.cpp"
#include "parking.cpp"
#include "unknown.cpp"
#include "figurel.cpp"
#include "checkmotor.cpp"
#include "Nihonbashi.cpp"
#include "catch_gray.cpp"
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
	    Unknown unknown;
	    PIDrun pidrun;
        Nihonbashi nihonbashi;
	    Parking par;
	    CatchGray catchg;
	//  nihonbashi.stop_ex();
      //int trace_side = pidrun.fix_position(); //左で見つかると1を返す
	    while(1){
	        //bar.search_bord();
	        //pidrun.pid_running(0); //引数は1(leftEdge)か1以外(rightEdge)
	    }
	    //ce.change_edge(ret_pid,line);
	    //clock.wait(9);
	    //}
    }
		//bar.barcode(pidrun.retw(),pidrun.retb());
        //unknown.Capture_unknown(bar.array);
}
