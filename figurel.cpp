using namespace ecrobot;
extern "C"
{
#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h"
#define MOTOR_B 0
#define MOTOR_C 1

    class Figurel{
    public:

        Cal cal;
        Drive dri;
        SensorGet sen;
        
        void figurel()
        {

            bar.search_bord(30,true);
            bar.ride_bord(600);

            /*motorB.reset();
            motorC.reset();
            
            while(motorB.getCount() > -500 && motorC.getCount() > -500){
              pidrun.pid_running(0,0);
            }*/

            while(true){
              pidrun.pid_running(0,0);


              int ava = sen.ret_avarage();//値が取れているか要確認
              int nowl = sen.nowlight();//値が取れているか要確認

              int i = cal.send_i_value(ava,nowl);


              //値が変わっているかの確認用
              //pid_runningと合わせる場合はdisplay()をコメントアウトする必要があるかも
              lcd.clear();
              lcd.putf("sdn", "i", i,10);
              lcd.putf("sdn","ava",ava,10);
              lcd.putf("sdn","nowl",nowl,10);
              lcd.disp();

              if(i < 0 && i > -100000){
                motorA.setPWM(0);
                motorB.setPWM(0);
                motorC.setPWM(0);
                clock.wait(100000);
              }
            }


            //値が変わっているかの確認用
            //pid_runningと合わせる場合はdisplay()をコメントアウトする必要があるかも
            /*lcd.clear();
            lcd.putf("sdn", "i", i,10);
            lcd.disp();*/



            //以下は後ほど変更
            /*motorB.setPWM(100);
            motorC.setPWM(100);
            clock.wait(200);
            motorC.setPWM(-100);
            motorB.setPWM(-100);
            clock.wait(300);
            motorB.setPWM(0);
            motorC.setPWM(0);*/





            /*
            while(1)
            {
                //板とタイヤを付けた状態から
                //灰色検知から少し前に進むとか入れるかも
                barcode.ride_bord(300);
                
                dri.forward(370,60,60,MOTOR_C);
                
                //立って止まる（関数で作った方がいいかも？急に止まると倒れるので徐々にスピードを落とさないといけない）
                motorB.setPWM(100);
                motorC.setPWM(100);
                clock.wait(300);
                motorC.setPWM(-100);
                motorB.setPWM(-100);
                clock.wait(500);
                motorB.setPWM(-70);
                motorC.setPWM(-70);
                clock.wait(300);
                motorC.setPWM(-50);
                motorB.setPWM(-50);
                clock.wait(250);
                motorB.setPWM(-20);
                motorC.setPWM(-20);
                clock.wait(250);
                motorC.setPWM(0);
                motorB.setPWM(0);
                
                clock.wait(5000);
                
                dri.forward(290,0,60,MOTOR_C);
                //立って方向転換するまで
                //何故か右斜めに進むからちょっと左斜め向きに入れないといけない？
                //↑これは本体が決まってから値を細かく調整
                clock.wait(15000);
                
                //倒れてちょい進んだあとPID復帰or新幹線へ？
                

                
            }
            */

        }
    };
}
