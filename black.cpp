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

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        
        int nowl;
        int ret_cal = 300;
        int ava;


        ava = lightavarage();
        
        while(1)
        {
            
            nowl = nowlight();
            ret_cal = p_i_d(ava,nowl);
            lcd.clear();
            lcd.putf("d", ret_cal);
            lcd.disp();
            
            motorbc(ret_cal);
            
            
            clock.wait(5);
        }


    }
}