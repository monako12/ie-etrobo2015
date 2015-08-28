/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot C++ API
#include "Clock.h"
#include "Lcd.h"
#include "Motor.h"
#include <Speaker.h>
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

        
        
        motorB.setPWM(100);
        motorC.setPWM(100);
        clock.wait(200);
        motorC.setPWM(-100);
        motorB.setPWM(-100);
        clock.wait(700);
        motorB.setPWM(-70);
        motorC.setPWM(-70);
        clock.wait(400);
        motorC.setPWM(-50);
        motorB.setPWM(-50);
        clock.wait(400);
        motorB.setPWM(-20);
        motorC.setPWM(-20);
        clock.wait(400);
        motorC.setPWM(0);
        motorB.setPWM(0);
        clock.wait(400);
        motorB.setPWM(30);
        motorC.setPWM(50);
        clock.wait(1000);
        motorC.setPWM(50);
        motorB.setPWM(30);
        clock.wait(950);
        motorB.setPWM(80);
        motorC.setPWM(0);
        motorA.setPWM(100);
        clock.wait(4400);
        
        motorB.setPWM(0);
        motorC.setPWM(0);
        clock.wait(3300);
        motorC.setPWM(100);
        motorB.setPWM(100);
        clock.wait(140);
        motorB.setPWM(0);
        motorC.setPWM(0);




        

    }
}
