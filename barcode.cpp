#include "math.h"
#include "stdlib.h"
#include "clock.h"
#include "motor.h"
using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
	Motor motorAA(PORT_A);
	Motor motorBB(PORT_B);
	Motor motorCC(PORT_C);
    int now;
    Clock clocktime;


    void fix_Direction(){
        now = motorAA.getCount();
        while(0 != now){
            motorAA.setPWM(now * (-1));
            clocktime.wait(5);
            now = motorAA.getCount();
        }
    }

    void discover(){
        motorBB.setPWM(0);
        motorCC.setPWM(0);
        fix_Direction();
        while(1){
            motorBB.setPWM(55);
            motorCC.setPWM(50);
        }
    }
}