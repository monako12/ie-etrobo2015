/*
This class is check the voltage.
by suzuki
*/

using namespace ecrobot;

extern "C"
{

  class Battery{
    public:
      int battery;

      void motor_battery(){  //電圧が7000以下なら停止する関数
        int v = 7000;

        if(battery > v){
          motorB.setPWM(30);
          motorC.setPWM(30);
          motorA.setPWM(30);
        }
        else{
          motorB.setPWM(0);
          motorC.setPWM(0);
          motorA.setPWM(0);

        }
      }

      void motor_battery_pro(){//電圧によって速度を変化させる
        int v1 = 6900;
        int v2 = 6800;
        int v3 = 6700;

              if(battery > v1){
                motorB.setPWM(50);
                motorC.setPWM(50);
                motorA.setPWM(50);
              }
              else if(battery > v2){
                motorB.setPWM(30);
                motorC.setPWM(30);
                motorA.setPWM(30);
              }
              else if(battery > v3){
                motorB.setPWM(20);
                motorC.setPWM(20);
                motorA.setPWM(20);
              }
              else{
                motorB.setPWM(0);
                motorC.setPWM(0);
                motorA.setPWM(0);
              }
          }

          int battery_main(){   //電圧を画面に出力
            battery = ecrobot_get_battery_voltage();

            motor_battery_pro();

            lcd.clear();
            lcd.putf("sdn","voltage[mV]:",battery,0);
            lcd.disp();
            clock.wait(500);
          }


      };
    }
