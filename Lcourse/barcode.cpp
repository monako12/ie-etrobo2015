#include "vector"
using namespace std;
//9/30
#define COUNT 50
#define MOTORCOUNT -45 //barcode ikko bunn no haba  tyousei hituyou
#define LEFT -26 //kotei de onegaisimasu
#define RIGHT -26
#define BORDER 16

extern "C"
{

	Motor motorAA(PORT_A);
	Motor motorBB(PORT_B);
	Motor motorCC(PORT_C);
    Clock clocktime;
    LightSensor  light_bar(PORT_3,true);
	GyroSensor   gyro_bar(PORT_1);
	PIDrun pidrun;

    class Barcode{
        public:
            vector<int> array;
        void fix_Direction(int hope){ //sei no suu de migi muku
            int now;
            int diff;
            while(true){
                now = motorAA.getCount();
                diff = hope - now;

                if(abs(diff) < 3){
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

        void acquire(int white,int black){
            int white_num = 0;
            int except = 0;
            int now_color = 0;
            int now_motor = 0;

            while(1){
                now_color = light_bar.getBrightness();
                pidrun.pid_running(2,-23,0,0);
                if(white + 10 < now_color){ //tyousei hituyou
                    white_num++;
                }

                if(60 == white_num){
                    motorAA.setPWM(0);
                            //motorBB.setPWM(0);    //barcode no saisyo wo tyotto dake susumu tyousei ni tukau yatu
                            //motorCC.setPWM(0);    //kokode stop sasete 109gyoume no atai wo tyousei suru
                    break;
                }
                lcd.clear();
                lcd.putf("sdn","white_num:",white_num,0);
                lcd.putf("sdn","now_color:",now_color,0);
                lcd.disp();
                clocktime.wait(1);
            }

            motorBB.setPWM(0);
            motorCC.setPWM(0);
            fix_Direction(-15);
            clock.wait(1000);
            motorBB.setPWM(LEFT);
            motorCC.setPWM(RIGHT);

            except = motorBB.getCount() + MOTORCOUNT;
            lcd.clear();
            int num=0;

            while(9 > array.size()){
                now_motor = motorBB.getCount();
                lcd.clear();
                lcd.putf("sdn","except:",except,0);
                lcd.putf("sdn","now_motor:",now_motor,0);
                if(now_motor == except){
                    now_color = light_bar.getBrightness();
                    if(white - 5 < now_color){ //tyousei hituyou
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
            motorBB.setPWM(0);
            motorCC.setPWM(0);
        }

        void barcode(int white,int black){
            ride_bord_final(false);
            clock.wait(1000);
            acquire(white,black);
            lcd.clear();
            for(int i=0; i<8; i++){
                lcd.putf("d",array[i],0);
            }

            lcd.disp();
            clocktime.wait(1000);
            fix_Direction(-30);
            motorCC.setPWM(-50);//yomitottara sonomama
            motorBB.setPWM(-35);//hashiritudukeru
            clocktime.wait(350);
            motorBB.setPWM(0);
            motorCC.setPWM(0);
            clock.wait(1000);
            search_bord(20,3);
            clock.wait(1000);
        }

        void ride_bord_final(bool check){
            int hoge;
            if(true == check){
                hoge = 3;
            }else{
                hoge = 2;
            }
            search_bord(16,hoge);
            motorAA.setPWM(0);
            fix_Direction(-60);
            clock.wait(400);
            ride_bord2(300);
            fix_Direction(60);
            search_bord(13,hoge);
            motorB.setPWM(-20);
            clock.wait(400);
            motorB.setPWM(0);
            clock.wait(1000);
            ride_bord2(300);
            fix_Direction(0);
        }

        void L_ride_bord(bool check){
            int hoge;
            if(true == check){
                hoge = 3;
            }else{
                hoge = 2;
            }
            search_bord(13,hoge);
            motorAA.setPWM(0);
            fix_Direction(-60);
            clock.wait(400);
            ride_bord2(450);
            fix_Direction(0);
            search_bord(13,hoge);
            fix_Direction(-10);
            ride_bord2(300);
        }

        void ride_bord2(int time){
            motorBB.setPWM(-73);
            motorCC.setPWM(-73);
            clock.wait(time);
            motorBB.setPWM(0);
            motorCC.setPWM(0);
            clock.wait(1000);
        }

        void ride_bord(int time){
            int velocity;
            int borderline;
            int diff_gyro;
            bool flag = false;

            gyro_bar.setOffset(0);
            motorAA.setPWM(0);
            motorBB.setPWM(-20);
            motorCC.setPWM(-20);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;
                lcd.clear();
                if(flag){
                    motorBB.setPWM(0);
                    motorCC.setPWM(0);
                    lcd.putf("sn","hoge");
                    lcd.putf("sdn","diff:",diff_gyro,0);
                    lcd.putf("sdn","border:",borderline,0);
                    lcd.putf("sdn","now:",velocity,0);
                    lcd.disp();
                    clocktime.wait(800);
                    break;
                }
                if(diff_gyro > BORDER){
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(800);
                    motorCC.setPWM(-60);
                    motorBB.setPWM(-60);
                    clocktime.wait(time);
                    flag = true;
                }
                lcd.putf("sdn","diff:",diff_gyro,0);
                lcd.disp();
                clocktime.wait(5);
            }
        }

        void ride_bord_kai(int time){
            fix_Direction(0);
            Get_off_straight(20,20,20);
            ride_bord2(180);
            clock.wait(800);
            Get_off_straight(25,25,13);
            //motorB.setPWM(-22);
            //clock.wait(400);
            motorC.setPWM(-22);
            clock.wait(550);
            //motorB.setPWM(-22);
            //clock.wait(400);
            ride_bord2(200);
            motorBB.setPWM(0);
            motorCC.setPWM(0);
            /*int velocity;
            int borderline;
            int diff_gyro;
            bool flag = false;

            gyro_bar.setOffset(0);
            motorAA.setPWM(0);
            motorBB.setPWM(-20);
            motorCC.setPWM(-23);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;
                lcd.clear();
                if(flag){
                    motorBB.setPWM(0);
                    motorCC.setPWM(0);
                    lcd.putf("sn","hoge");
                    lcd.putf("sdn","diff:",diff_gyro,0);
                    lcd.putf("sdn","border:",borderline,0);
                    lcd.putf("sdn","now:",velocity,0);
                    lcd.disp();
                    clocktime.wait(800);
                    break;
                }
                if(diff_gyro > BORDER){
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(800);
                    motorCC.setPWM(-70);
                    motorBB.setPWM(-60);
                    clocktime.wait(time);
                    flag = true;
                }
                lcd.putf("sdn","diff:",diff_gyro,0);
                lcd.disp();
                clocktime.wait(5);
            }*/
        }

        void search_bord(int border,int select){
            int velocity;
            int borderline;
            int diff_gyro;

            gyro_bar.setOffset(0);
            motorAA.setPWM(0);
            motorBB.setPWM(-20);
            motorCC.setPWM(-20);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                pidrun.pid_running(select,-17,300,80);
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;

                if(diff_gyro > border){ //tyousei hituyou
                    motorAA.setPWM(0);
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(1000);
                    break;
                }
            }
        }

        void search_bord2(int border,int select){
            int velocity;
            int borderline;
            int diff_gyro;

            gyro_bar.setOffset(0);
            motorAA.setPWM(0);
            motorBB.setPWM(-20);
            motorCC.setPWM(-20);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                pidrun.pid_running(select,-5,40,70);
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;

                if(diff_gyro > border){ //tyousei hituyou
                    motorAA.setPWM(0);
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(1000);
                    break;
                }
            }
        }

        void Get_off_straight(int b,int c,int border){
            int velocity;
            int borderline;
            int diff_gyro;
            int now_motor;
            int before_motor;
            int diff_motor;
            int check_motor=0;

            before_motor = motorB.getCount();
            gyro_bar.setOffset(0);
            motorAA.setPWM(0);
            motorBB.setPWM(-b);
            motorCC.setPWM(-c);
            borderline = gyro_bar.getAnglerVelocity();

            while(true){
                velocity = gyro_bar.getAnglerVelocity();
                now_motor = motorB.getCount();
                diff_gyro = velocity - borderline;
                diff_motor = now_motor - before_motor;

                if(diff_gyro > border){ //tyousei hituyou
                    motorAA.setPWM(0);
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(1000);
                    break;
                }

                if(-2 < diff_motor && diff_motor >> 2){
                    check_motor++;
                    if(200 == check_motor){
                    motorAA.setPWM(0);
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(1000);
                    break;
                    }
                }
                before_motor = now_motor;
            }
        }
    };
}