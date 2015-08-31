/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot C++ API
#include "Clock.h"
#include "drive.cpp"
#include "calculation.cpp"
#include "sensor.cpp"
#include "Lcd.h"

using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// nxtOSEK hook to be invoked from an ISR in category 2
    void user_1ms_isr_type2(void)
    {

    }
    
    void logSend()
    {
        U8 data_log_buffer[32];

        *((S32 *)(&data_log_buffer[8]))  = (S32)motorA.getCount();
        *((S32 *)(&data_log_buffer[12])) = (S32)motorB.getCount();
        *((S32 *)(&data_log_buffer[16])) = (S32)motorC.getCount();
        lcd.putf("d", 0);

        ecrobot_send_bt_packet(data_log_buffer, 32);
    }
    

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        
        int nowl;
        int ret_pid = 300;
        int ava;
        int sum;

        ava = lightavarage();
        int line;
        while(1)
        {

            nowl = nowlight(ava);
            line = cur_ava(nowl,ava);
            ret_pid = p_i_d(ava,nowl);
            sum = ret_sum();
            //curve(sum,line);
            lcd.clear();
            lcd.putf("d", ret_pid);
            lcd.disp();
            mo(ret_pid,line,sum);
            logSend();
                    
            clock.wait(3);
        }
    }
}
