/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot C++ API
#include "Clock.h"
#include "Lcd.h"
#include "Motor.h"
#include "BTConnection.h"
#include "Bluetooth.h"
#include "LightSensor.h"
using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
    Motor motorA(PORT_A);
    Motor motorB(PORT_B);
    Motor motorC(PORT_C);
    LightSensor  light(PORT_3,true);



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

        ecrobot_send_bt_packet(data_log_buffer, 32);
    }

    TASK(TaskMain)
    {
        Clock clock;
        Lcd lcd;
        int a = 8;


        
        
        motorB.setPWM(100);
        motorC.setPWM(100);
        clock.wait(200);
        motorC.setPWM(-100);
        motorB.setPWM(-100);
        clock.wait(700);
        motorB.setPWM(-70);
        motorC.setPWM(-70);
        clock.wait(500);
        motorC.setPWM(-50);
        motorB.setPWM(-50);
        clock.wait(400);
        motorB.setPWM(-20);
        motorC.setPWM(-20);
        clock.wait(400);
        motorC.setPWM(0);
        motorB.setPWM(0);
        clock.wait(400);
        motorB.setPWM(-30);
        motorC.setPWM(70);
        clock.wait(1000);
        motorC.setPWM(70);
        motorB.setPWM(-30);
        clock.wait(890);
        motorB.setPWM(80);
        motorC.setPWM(0);
        motorA.setPWM(100);
        clock.wait(4250);
        logSend();
        motorB.setPWM(0);
        motorC.setPWM(0);
        clock.wait(3300);
        motorC.setPWM(100);
        motorB.setPWM(100);
        clock.wait(130);
        motorB.setPWM(0);
        motorC.setPWM(0);




        

    }
    
}
