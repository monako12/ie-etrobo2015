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
//        fig.figurel();
	    Unknown unknown;
	    PIDrun pidrun;
        Nihonbashi nihonbashi;
	    Parking par;
	    CatchGray catchg;
      //int trace_side = pidrun.fix_position(); //左で見つかると1を返す
	    //ce.change_edge(ret_pid,line);
	    //clock.wait(9);
	    //}
	    while(1){
	        //If you do test program,you have to write in this while loop.
		//bar.barcode(pidrun.retw(),pidrun.retb());
        //unknown.Capture_unknown(bar.array);
	    }
    }
}
