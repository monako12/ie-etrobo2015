//made by okada
#include "Motor.h"
#include "math.h"
#include "stdlib.h"
#include "Lcd.h"

using namespace ecrobot;
extern "C"
{
#define MOTOR_B 0
#define MOTOR_C 1

  Motor motorA(PORT_A);
  Motor motorB(PORT_B);
  Motor motorC(PORT_C);
  Clock clock;
  Lcd lcd;
  SensorGet sensor;
  Cal cal;

  class Drive{
  public:
    int nrotate; //現在の回転数
    int srotate; //初期の回転数
    int position();
    void motor_count_reset();
    void motor_stop();
    void Right_Edge_Trace(int, int, int, int);
    void Left_Edge_Trace(int, int, int, int);
    void dash(int, int);
		void dash_left(int,int);
    int RightSide_line_check(int, int);
    int LeftSide_line_check(int, int);
    void Return_to_position(bool);
    int fix_position(int, int, int, int, int);
    void back(int);
    int power_Adjustment(int, int);
    void motorA_position_set(int);
    void angle(int, int);
    void forward(int, int, int, int);
    void bforward(int, int);
	void Barcode_pid_run(int, int, int);
	void slow_Trace(int, int, int);
      void lforward(int, int, int, int);
      void lbforward(int,int);
  };

  int Drive::position(){
    return((motorB.getCount()+motorC.getCount())/2);
  }

  void Drive::motor_count_reset(){
    motorB.reset();
    motorC.reset();
  }

  void Drive::motor_stop(){
    motorA.setPWM(0);
    motorB.setPWM(0);
    motorC.setPWM(0);
  }

  void Drive::Right_Edge_Trace(int pid,int line,int width,int Apower){
    int b,c;
    if(line < 0){
      if(motorA.getCount() <= width){
	motorA.setPWM(Apower);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() >= -width){
	motorA.setPWM(-Apower);
      }else{
	motorA.setPWM(0);
      }
    }
    if(pid < 0){
      b = - 50 + pid/3;
      c = - 35 - pid/3;
    }else{
      b = - 45 + pid/3;
      c = - 40 - pid/3;
    }
    motorC.setPWM(c);
    motorB.setPWM(b);
  }

  void Drive::Left_Edge_Trace(int pid,int line,int width,int Apower){
    int b,c;
    if(line < 0){
      if(motorA.getCount() >= -width){
	motorA.setPWM(-Apower);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() <= width){
	motorA.setPWM(Apower);
      }else{
	motorA.setPWM(0);
      }
    }
    if(pid < 0){
      b = -35 - pid/3;
      c = -50 + pid/3;
    }else{
      b = -40 - pid/3;
      c = -45 + pid/3;
    }

    motorC.setPWM(c);
    motorB.setPWM(b);
  }

  void Drive::dash(int pid,int line){
    if(line < 0){
      if(motorA.getCount() >= -20){
	motorA.setPWM(-50);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() <= 20){
	motorA.setPWM(50);
      }else{
	motorA.setPWM(0);
      }
    }
    int b;
    int c;
    if(pid < 0){
      b = -90 + (pid/3);
      c = -80 - (pid/3);
    }else{
      b = -90 + (pid/3);
      c = -85 - (pid/3);
    }
    motorC.setPWM(c);
    motorB.setPWM(b);
  }

	void Drive::dash_left(int pid,int line){
    int b,c;
    if(line < 0){
      if(motorA.getCount() >= -20){
	motorA.setPWM(-10);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() <= 20){
	motorA.setPWM(10);
      }else{
	motorA.setPWM(0);
      }
    }
    if(pid < 0){
      b = -80 - pid/4;
      c = -90 + pid/4;
    }else{
      b = -85 - pid/4;
      c = -90 + pid/4;
    }

    motorC.setPWM(c);
    motorB.setPWM(b);
  }

  int Drive::RightSide_line_check(int light_value, int black_line){
    int find_out = 0;
    if(motorA.getCount() <= 200){
      motorA.setPWM(60);
    }else{
      motorA.setPWM(0);
    }
    motorB.setPWM(-90);
    motorC.setPWM(-10);
    //if(light_value <= black_line+20){
    if(light_value <= black_line+70){
      find_out = 1;
    }
    return find_out;
  }

  int Drive::LeftSide_line_check(int light_value, int black_line){
    int find_out = 0;
    if(motorA.getCount() >= -200){
      motorA.setPWM(-60);
    }else{
      motorA.setPWM(0);
    }
    motorB.setPWM(-10);
    motorC.setPWM(-90);
    if(light_value <= black_line+20){
      find_out = 1;
    }
    return find_out;
  }

  void Drive::Return_to_position(bool side){
    if(side == true){
      while(0 >= position()){
	motorB.setPWM(10);
	motorC.setPWM(90);
      }
    }else{
      while(0 >= position()){
	motorB.setPWM(90);
	motorC.setPWM(10);
      }
    }
  }

  int Drive::fix_position(int pid, int light_value, int line_side, int back_distance, int black_line){
    int B_power, C_power;
    int slow_power = 0;
    int fast_power = 1;
    int distance = position();;
    if(light_value > black_line+20){
      if(line_side == 0){  //ラインが左にあるときの処理
	if(motorA.getCount() >= -300){
	  motorA.setPWM(-80);
	}else{
	  motorA.setPWM(0);
	}
	B_power = power_Adjustment(pid, slow_power);
	C_power = power_Adjustment(pid, fast_power);
      }else if(line_side == 1){ //ラインが右にあるときの処理
	if(motorA.getCount() <= 300){
	  motorA.setPWM(80);
	}else{
	  motorA.setPWM(0);
	}
	B_power = power_Adjustment(pid, fast_power);
	C_power = power_Adjustment(pid, slow_power);
      }
      motorB.setPWM(B_power);
      motorC.setPWM(C_power);
      distance = position();
    }else{
      motor_stop();
      clock.wait(1000);
      motor_count_reset();
      while(position()<(-distance/3)){
	back(line_side);
      }
      back_distance = -distance/3;
      motor_stop();
      motorA_position_set(100);
      clock.wait(1000);
    }
    return back_distance;
  }

  void Drive::back(int line_sides){
    if(line_sides == 0){ //ラインが左にある時
      if(motorA.getCount() >= -300){
	motorA.setPWM(-80);
      }else{
	motorA.setPWM(0);
	motorB.setPWM(10);
	motorC.setPWM(30);
      }
    }else if(line_sides == 1){ //ラインが右にある時
      if(motorA.getCount() <= 300){
	motorA.setPWM(80);
      }else{
	motorA.setPWM(0);
	motorB.setPWM(30);
	motorC.setPWM(10);
      }
    }

  }

  int Drive::power_Adjustment(int pid, int power){
    int return_Power;
    if(pid >= 80) pid = 80;
    if(power == 1){
      return_Power = -pid;
    }else{
      if((-pid - position()/2) <= -50){
	return_Power = -60;
	}else if(-pid - position()/2 >= -10){
	return_Power = -10;
      }else{
	return_Power = (-pid - position()/2);
      }
    }
    return return_Power;
  }

  void Drive::motorA_position_set(int range){
    if(range < 0) range *= -1;
    while(motorA.getCount() >= range || -1*range >= motorA.getCount()){
      if(motorA.getCount() <= 0){
	motorA.setPWM(40);
      }else{
	motorA.setPWM(-40);
      }
    }
  }

  void Drive::angle(int number,int speed){
    srotate = nxt_motor_get_count(PORT_A);
                while(1){
                    nrotate = nxt_motor_get_count(PORT_A);
                    if (nrotate < (srotate + number)){
                        motorA.setPWM(speed);
                    }
                    else if (nrotate > (srotate + number)){
                        motorA.setPWM((-1) * speed);
                    }
                    else {
                        motorA.setPWM(0);
                        break;
                    }
                }
  }

  void Drive::forward(int number,int lspeed,int rspeed,int tire){
    if (tire == MOTOR_B){
      srotate = nxt_motor_get_count(PORT_B);
    } else if (tire == MOTOR_C) {
      srotate = nxt_motor_get_count(PORT_C);
    }
    while(1){
      if (tire == MOTOR_B){
	nrotate = nxt_motor_get_count(PORT_B);
      } else if (tire == MOTOR_C) {
	nrotate = nxt_motor_get_count(PORT_C);
      }
      if (nrotate > (srotate + ((-1) * number))){
	motorB.setPWM((-1) * lspeed);
	motorC.setPWM((-1) * rspeed);
      }
      else if (nrotate < (srotate + ((-1) * number))){
	motorB.setPWM(lspeed);
	motorC.setPWM(rspeed);
      }
      else {
	motorB.setPWM(0);
	motorC.setPWM(0);
	break;
      }
    }
    }

  void Drive::bforward(int lspeed,int rspeed){
    while(1){
      int now = sensor.nowlight();
      int ava = sensor.ret_avarage();
      int color = cal.cur_ava(now,(double)ava);
      if (color < 0){
	motorB.setPWM(0);
	motorC.setPWM(0);
	break;
      }
      else if (color > 0){
	motorB.setPWM((-1) * lspeed);
	motorC.setPWM((-1) * rspeed);
      }
    }
  }

  void Drive::Barcode_pid_run(int pid,int line,int fix){
    int b,c;
    if(line < 0){
      if(motorA.getCount() <= 350){
	motorA.setPWM(70);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() >= -350){
	motorA.setPWM(-70);
      }else{
	motorA.setPWM(0);
      }
    }
    if(pid < 0){
      b = - 50 + pid/3 - fix;
      c = - 35 - pid/3 - fix;
    }else{
      b = - 45 + pid/3 - fix;
      c = - 40 - pid/3 - fix;
    }
    motorC.setPWM(c);
    motorB.setPWM(b);
  }

  void Drive::slow_Trace(int pid,int line,int fix){
    int b,c;
    if(line < 0){
      if(motorA.getCount() >= -350){
	motorA.setPWM(-80);
      }else{
	motorA.setPWM(0);
      }
    }else{
      if(motorA.getCount() <= 350){
	motorA.setPWM(80);
      }else{
	motorA.setPWM(0);
      }
    }
    if(pid < 0){
      b = -35 - pid/3 - fix;
      c = -50 + pid/3 - fix;
    }else{
      b = -40 - pid/3 - fix;
      c = -45 + pid/3 - fix;
    }

    motorC.setPWM(c);
    motorB.setPWM(b);
  }
    
    void Drive::lforward(int number,int lspeed,int rspeed,int tire){
        if (tire == MOTOR_B){
            srotate = nxt_motor_get_count(PORT_B);
        } else if (tire == MOTOR_C) {
            srotate = nxt_motor_get_count(PORT_C);
        }
        while(1){
            if (tire == MOTOR_B){
                nrotate = nxt_motor_get_count(PORT_B);
            } else if (tire == MOTOR_C) {
                nrotate = nxt_motor_get_count(PORT_C);
            }
            if (nrotate > (srotate + ((-1) * number))){
                motorB.setPWM((-1) * lspeed);
                motorC.setPWM((-1) * rspeed);
            }
            else if (nrotate < (srotate + ((-1) * number))){
                motorB.setPWM(lspeed);
                motorC.setPWM(rspeed);
            }
            else {
                break;
            }
        }
    }
    
    void Drive::lbforward(int lspeed,int rspeed){
        while(1){
            int now = sensor.nowlight();
            int ava = sensor.ret_avarage();
            int color = cal.cur_ava(now,(double)ava);
            if (color < 0){
                break;
            }
            else if (color > 0){
                motorB.setPWM((-1) * lspeed);
                motorC.setPWM((-1) * rspeed);
            }
        }
    }

}
