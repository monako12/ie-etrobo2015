#include "math.h"
#include "stdlib.h"
#include "clock.h"
#include "motor.h"
#include "Lightsensor.h"
#include "vector"
using namespace ecrobot;
using namespace std;

#define COUNT 50
#define MOTORCOUNT -55 //barcode ikko bunn no haba
#define LEFT -26 //kotei de onegaisimasu
#define RIGHT -24

extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
	Motor motorAA(PORT_A);
	Motor motorBB(PORT_B);
	Motor motorCC(PORT_C);
    Clock clocktime;
    LightSensor  light_b(PORT_3,true);

    int check = 0;
    vector<int> array;


    void fix_Direction(int piyo){ //siteisita kazu no tyotto migi made zenrin wo mawasu
        int now;
        int diff;
        while(true){
            now = motorAA.getCount();
            diff = piyo - now;

            if(abs(diff) < 3){
                motorAA.setPWM(-100);//ittan migi muku
                clocktime.wait(50);
                motorAA.setPWM(0);
                break;
            }

            if(diff > 0){
                motorAA.setPWM(100);
            }else{
                motorAA.setPWM(-100);
            }
        }
    }

    void getbar(int white, int black){  //kekkyoku tukattenai
        int review;
        int white_num = 0;
        int black_num = 0;
        while(1){
            review = light_b.getBrightness();
            if(white - 25 < review && white + 25 > review){
                white_num++;
                check++;
            }

            if(black - 25 < review && black + 25 > review){
                black_num++;
                check++;
            }

            lcd.clear();
            lcd.putf("dn", review,0);
            lcd.putf("sdn","white_num:",white_num,0);
            lcd.putf("sdn","black_num:",black_num,0);
            lcd.putf("sdn","white:",white,0);
            lcd.putf("sdn","black:",black,0);
            lcd.putf("sdn","check:",check,0);
          	lcd.disp();
          	clocktime.wait(5);

            if(COUNT == white_num) {
         	    array.push_back(0);
          	    white_num = 0;
          	}

          	if(COUNT == black_num) {
         	    array.push_back(1);
          	    black_num = 0;
           	}

          	if(10 == array.size()) break;
          	motorBB.setPWM(-26);
            motorCC.setPWM(-19);
        }

    }

    void acquire(int white,int black){
        int review;
        int white_num = 0;
        int except = 0;
        int now_color = 0;
        int now_motor = 0;

        motorBB.setPWM(LEFT);
        motorCC.setPWM(RIGHT);

        while(1){
            review = light_b.getBrightness();
            if(white - 15 < review && white + 15 > review){
                white_num++;
            }

            if(30 == white_num){
                motorAA.setPWM(0);
//                        motorBB.setPWM(0);    //barcode no saisyo wo tyotto dake susumu tyousei ni tukau yatu
//                        motorCC.setPWM(0);    //kokode stop sasete 109gyoume no atai wo tyousei suru
                break;
            }
            lcd.clear();
            lcd.putf("sdn","white_num:",white_num,0);
            lcd.disp();
            clocktime.wait(1);
        }

/*
        motorBB.setPWM(0);
        motorCC.setPWM(0);
        clocktime.wait(500);
        motorBB.setPWM(LEFT);
        motorCC.setPWM(RIGHT);*/

        except = motorBB.getCount() + MOTORCOUNT;
        lcd.clear();
        int num=0;

        while(9 > array.size()){
            now_motor = motorBB.getCount();
            lcd.clear();
            lcd.putf("sdn","except:",except,0);
            lcd.putf("sdn","now_motor:",now_motor,0);
            if(now_motor == except){
                now_color = light_b.getBrightness();
                if(white - 30 < now_color && white + 30 > now_color){
                    array.push_back(0);
                    except += MOTORCOUNT;
                    lcd.putf("sn","0");
                }else{
                    array.push_back(1);
                    except += MOTORCOUNT;
                    lcd.putf("sn","0");
                }
            }
            num = array.size();
            lcd.putf("sdn","array_size:",num,0);
            lcd.putf("sdn","white_num:",white_num,0);
            lcd.disp();
            clocktime.wait(1);
        }

    }


    void barcode(int white,int black){
        motorBB.setPWM(0);
        motorCC.setPWM(0);
        fix_Direction(0);
 //       getbar(white,black);
        acquire(white,black);

        motorBB.setPWM(0);
        motorCC.setPWM(0);
        lcd.clear();
        for(int i=0; i<8; i++){
            lcd.putf("d",array[i],0);
        }

        lcd.disp();
        while(1){

        }
    }
}