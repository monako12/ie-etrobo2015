#include "math.h"
#include "stdlib.h"
#include "clock.h"
#include "motor.h"
#include "Lightsensor.h"
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
    LightSensor  light_b(PORT_3,true);


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

    void barcode(int white,int black){
        int review;
        motorAA.setPWM(-100);
        clocktime.wait(500);
        motorBB.setPWM(0);
        motorCC.setPWM(0);
        fix_Direction(0);

        while(1){
            review = light_b.getBrightness();
            lcdhoge.clear();
            lcd.putf("d", review);
            lcd.putf("¥n");

         	lcd.disp();
         	clocktime.wait(10);
            motorBB.setPWM(-25);
            motorCC.setPWM(-20);
        }
    }
}