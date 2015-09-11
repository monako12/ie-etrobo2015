#include "vector"
using namespace std;

#define COUNT 50
#define MOTORCOUNT -45 //barcode ikko bunn no haba  tyousei hituyou
#define LEFT -26 //kotei de onegaisimasu
#define RIGHT -26

extern "C"
{

	Motor motorAA(PORT_A);
	Motor motorBB(PORT_B);
	Motor motorCC(PORT_C);
    Clock clocktime;
    LightSensor  light_bar(PORT_3,true);
	GyroSensor   gyro_bar(PORT_1);

    class Barcode{
        public:
            vector<int> array;
        void fix_Direction(int hope){ //siteisita kazu no tyotto migi made zenrin wo mawasu
            int now;
            int diff;
            while(true){
                now = motorAA.getCount();
                diff = hope - now;
    
                if(abs(diff) < 3){
                   // motorAA.setPWM(-100);//ittan migi muku
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

            motorBB.setPWM(LEFT); //pid seigyo ireyoukana?
            motorCC.setPWM(RIGHT);

            while(1){
                now_color = light_bar.getBrightness();
                if(white - 5 < now_color){ //tyousei hituyou
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
            clocktime.wait(800);
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
            fix_Direction(0);
            ride_bord(1000); //tyousei hituyou
            fix_Direction(0);
            acquire(white,black);
            lcd.clear();
            for(int i=0; i<8; i++){
                lcd.putf("d",array[i],0);
            }

            lcd.disp();
            clocktime.wait(500);
            motorCC.setPWM(-35);//yomitottara sonomama
            motorBB.setPWM(-35);//hashiritudukeru
            clocktime.wait(500);
            motorBB.setPWM(0);
            motorCC.setPWM(0);
        }

        void search_bord{
            int velocity;
            int borderline;
            int diff_gyro;
            bool flag=false;

            borderline = gyro_bar.getAnglerVelocity();

            gyro_bar.setOffset(0);
            while(flag){
                velocity = gyro_bar.getAnglerVelocity();
                diff_gyro = velocity - borderline;
                if(diff_gyro > 16){ //tyousei hituyou
                    motorCC.setPWM(0);
                    motorBB.setPWM(0);
                    clock.wait(800);
                    clocktime.wait(time);
                    flag = true;
                }
                lcd.putf("sdn","diff:",diff_gyro,0);
                lcd.disp();
                clocktime.wait(5);
            }
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
                if(diff_gyro > 16){ //tyousei hituyou
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
    };
}
