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
        int srotate;
        int nrotate;

        Cal cal;
        Drive drive;
        SensorGet sen;
        Parking par;
        
        void figurel()
        {
            clock.wait(2000);
            bar.ride_bord_final(true);
            /*motorA.setPWM(0);
            motorB.setPWM(0);
            motorC.setPWM(0);
            clock.wait(1000);*/

            while(true){
                srotate = nxt_motor_get_count(PORT_C);
                while(1){
                    nrotate = nxt_motor_get_count(PORT_C);
                    if (nrotate > (srotate + ((-1) * 350))){
                        pidrun.pid_running(false,0);
                    }
                    else {
                        break;
                    }
                }
                motorB.setPWM(0);
                motorC.setPWM(0);
                par.reset(100);
                clock.wait(2000);
                
                drive.angle(380,100);
                drive.bforward(70,70);
                drive.angle(-80,100);
                drive.forward(30,40,40,MOTOR_C);
                drive.angle(300,80);
                drive.bforward(50,0);
                
                drive.angle(680,100);
                drive.forward(30,80,0,MOTOR_B);
                par.reset(100);

                clock.wait(1000);
                
                while(1){
                    pidrun.pid_running(false,0);
                }
                /*
                 drive.angle(680,100);
                 drive.forward(30,80,0,MOTOR_B);
                 par.reset(100);
                 */
                
                
                /*pidrun.pid_running(0,0);
                 
                 
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
                 }*/
            }
            
            
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
