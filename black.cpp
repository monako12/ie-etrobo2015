/* sample.cpp for TOPPERS/ATK(OSEK) */ 
//made by okada
// ECRobot C++ API
#include "Clock.h"
#include "drive.cpp"
#include "calculation.cpp"
#include "sensor.cpp"
#include "barcode.cpp"
#include "change_edge.cpp"
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

    }

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        sensor sensor;
        Cal cal;

        
        int nowl;
        int ret_pid = 300;
        int ava;
        int sum;

        ava = sensor.lightavarage();
        int line;
        while(1)
        {
            nowl = sensor.nowlight(ava);
            line = cal.cur_ava(nowl,ava);
            ret_pid = cal.p_i_d(ava,nowl);
            sum = sensor.ret_sum();
            //curve(sum,line);
            lcd.clear();
            lcd.putf("d", ret_pid);
            lcd.disp();
            change_edge(ret_pid,line);
            
            clock.wait(5);


        }


    }
}
