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
    Clock clocktime;
    Lcd lcdhoge;


    void fix_Direction(int piyo){
        int now;
        int diff;
        while(true){
            now = motorAA.getCount();
            diff = piyo - now;

            if(abs(diff) < 3){
                motorAA.setPWM(200);//ittan migi muku
                clocktime.wait(10);
                motorAA.setPWM(0);
                break;
            }

            if(diff > 0){
                motorAA.setPWM(-200);
            }else{
                motorAA.setPWM(200);
            }

        }
    }

    void discover(int fuga){
        motorAA.setPWM(-100);
        clocktime.wait(1000);
        motorBB.setPWM(0);
        motorCC.setPWM(0);
        fix_Direction(fuga);

        while(1){
            motorBB.setPWM(-55);
            motorCC.setPWM(-50);
        }
    }
}