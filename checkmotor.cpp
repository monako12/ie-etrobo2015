extern "C"
{
    class Checkmotor{
        public:

        void checkmotor(){
            int b_motor = motorB.getCount();
            int c_motor = motorC.getCount();
            int result_b;
            int result_c;

            motorB.setPWM(-50);
            motorC.setPWM(-50);

            clock.wait(2000);
            motorB.setPWM(0);
            motorC.setPWM(0);
            clock.wait(500);
            result_b = b_motor - motorB.getCount();
            result_c = c_motor - motorC.getCount();
            lcd.clear();
            lcd.putf("sdn","motor_b:",result_b,0);
            lcd.putf("sdn","motor_c:",result_c,0);
            lcd.disp();
            while(true){
                clock.wait(100);
            }
        }
    };
}