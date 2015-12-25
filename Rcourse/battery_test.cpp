/*
This class is check the voltage.
by suzuki
*/

using namespace ecrobot;

extern "C"
{

  class Battery{
    private:
        int  battery;
        void motor_battery();
        void motor_battery_pro();
        void battery_disp();

    public:
        Battery();
        int  battery_main();
        int  get_voltage(){return(ecrobot_get_battery_voltage());};
        void fix_voltage(int adjust, int power);//目標値を引数として渡す
  };

      Battery::Battery(){
        battery = 0;
      }

      void Battery::motor_battery(){ //電圧が7000以下なら停止する関数
        const int V = 7000;

        if(battery > V){
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

      void Battery::motor_battery_pro(){//電圧によって速度を変化させる
        const int V1 = 6900;
        const int V2 = 6800;
        const int V3 = 6700;

          if(battery > V1){
            motorB.setPWM(50);
            motorC.setPWM(50);
            motorA.setPWM(50);
          }
          else if(battery > V2){
            motorB.setPWM(30);
            motorC.setPWM(30);
            motorA.setPWM(30);
          }
          else if(battery > V3){
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

      void Battery::fix_voltage(int adjust, int power){
        const int CONFIRM = 10;
              int count   = 0;

        adjust = adjust*100;

        while(count <= CONFIRM){ //adjust以下の値を10回確認したら終了。
            battery = get_voltage();
            battery_disp();
            if(battery <= adjust){
                count++;
            }
            else{
                motorB.setPWM(power);
                motorC.setPWM(power);
                motorA.setPWM(power);
            }
        }
        motorB.setPWM(0);
        motorC.setPWM(0);
        motorA.setPWM(0);
      }

      void Battery::battery_disp(){
        lcd.clear();
        lcd.putf("sdn","voltage[mV]:",battery,0);
        lcd.putf("sdn","Battery[%]:",battery/100,0);
        lcd.disp();
        clock.wait(1000);
      }

      int Battery::battery_main(){   //電圧を画面に出力
        battery = get_voltage();
        //処理に応じて変更
        battery_disp();
      }

}
