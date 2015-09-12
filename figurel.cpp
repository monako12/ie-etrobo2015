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
        Barcode barcode;
        
        void figurel()
        {
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
        }
    };
}
