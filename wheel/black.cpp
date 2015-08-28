/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot C++ API
#include "Clock.h"
#include "Lcd.h"
#include "Motor.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    Motor motorA(PORT_A);
    Motor motorB(PORT_B);
    Motor motorC(PORT_C);

// nxtOSEK hook to be invoked from an ISR in category 2
    void user_1ms_isr_type2(void)
    {

    }

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;

        
        int sum;


        while(1)
        {
            lcd.clear();
            lcd.putf("d",motorA.getCount(),0);
            lcd.disp();
            clock.wait(1000);
            motorA.setCount(0);

            clock.wait(10);


        }


    }
}
