/* sample.cpp for TOPPERS/ATK(OSEK) */ 

// ECRobot C++ API
#include "Clock.h"
#include "drive.cpp"
#include "calculation.cpp"
#include "sensor.cpp"


using namespace ecrobot;

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"

// nxtOSEK hook to be invoked from an ISR in category 2
    void user_1ms_isr_type2(void)
    {
  SleeperMonitor(); // needed for I2C device and Clock classes
}

TASK(TaskMain)
{
    Clock clock;
    Lcd lcd;
    while(touch.isPressed()==0)
    {
            //sensorの値を呼ぶ関数
        motora();
        clock.wait(5);
    }


}
}