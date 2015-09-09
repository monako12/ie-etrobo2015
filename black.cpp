/* sample.cpp for TOPPERS/ATK(OSEK) */
//made by okada
// ECRobot C++ API
#include "Clock.h"
#include "drive.cpp"
#include "calculation.cpp"
#include "sensor.cpp"
#include "pid_run.cpp"
#include "barcode.cpp"
#include "train.cpp"
#include "parking.cpp"
#include "unknown.cpp"
#include "figurel.cpp"
#include "checkmotor.cpp"

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
        sensor sensor;
        Cal cal;
        Barcode bar;
        Train train;
        Drive drive;
        Unknown unknown;
	    PIDrun pidrun;

        Checkmotor checkmotor;

//        int nowl;
//        int ret_pid = 300;
//        int ava;
        int sum;
        int pos;
//        ava = sensor.lightavarage();
        bool hoge=true;
//        int line;

	int count = 0;
	//	while(1){
	  /*nowl = sensor.nowlight(ava);
            line = cal.cur_ava(nowl,ava);
            ret_pid = cal.p_i_d(ava,nowl);
            sum = sensor.ret_sum();
	    pos = drive.position();*/
            //curve(sum,line);
            bar.barcode(sensor.ret_white(),sensor.ret_black());
            unknown.Capture_unknown(bar.array);
	pidrun.fix_position();
	//	while(drive.position()<100){
	drive.motor_count_reset();//後輪の回転数をリセット
	while(drive.position()<100){
	  pidrun.pid_running(false);
	}
	while(1){
	  pidrun.pid_dash();
	}
		lcd.clear();
		lcd.putf("dn",pos);
//		lcd.putf("d", ret_pid);
		lcd.disp();
            //ce.change_edge(ret_pid,line);
            clock.wait(9);
	    //}
	    }
}
