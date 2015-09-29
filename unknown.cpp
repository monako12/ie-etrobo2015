#define DISTANCE 20
extern "C"
{

    Barcode bar;
    Drive dri;
    Parking par;
    Train tra;
    

    class Unknown{
        public:
            int map[5][6];
            int start_pos;
            int end_pos;
            int array[8];
            vector<int> sol_route;
        int Check_barcode(vector<int> &temp){
            lcd.clear();
            if(temp[8] != 1){
                lcd.clear();
                lcd.putf("sn","no barcode");
                for(int i=0; i < 8; i++){
                    if(i%2 == 0){
                        lcd.putf("d",temp[i],0);
                    }else{
                        lcd.putf("dn",temp[i],1);
                    }
                }
                lcd.disp();
                Retire(801);
                return(1);
            }

            lcd.putf("sn","hoge");
            for(int i=0; i < 8; i++){
                array[i] = temp[i];
            }
            for(int i=0; i < 8; i++){
                if(i%2 == 0){
                    lcd.putf("d",array[i],0);
                }else{
                    lcd.putf("dn",array[i],1);
                }
            }
            lcd.disp();
            return(0);
        }

        void Make_map(){
            for(int i=0; i < 5; i++){
                for(int j=0; j<6; j++){
                    map[i][j] = 1;
                }
            }

            for(int i=0; i<5; i++){
                map[i][0] = 0;
                map[i][5] = 0;
            }

            for(int j=0; j<6; j++){
                map[4][j] = 5;
            }

            for(int j=0; j<4; j++){
                if(array[2*j] == 0){
                    if(array[2*j+1] == 0){
                        map[0][j+1] = 0;
                    }else{
                        map[1][j+1] = 0;
                    }
                }else{
                    if(array[2*j+1] == 0){
                        map[2][j+1] = 0;
                    }else{
                        map[3][j+1] = 0;
                    }
                }
            }
        }

        void Modify_map(){ //9_18
        /*
            int map_dummy[5][6]={ //test_date
                {  0,  1,  1,  1,  1,  0, },
                {  0,  0,  1,  1,  1,  0, },
                {  0,  1,  1,  0,  0,  0, },
                {  0,  1,  0,  1,  1,  0, },
                {  5,  5,  5,  5,  5,  5, },
            };
         */
            bool flag=true;//初期状態動作のためflag=1

            while(flag){
                flag = false;
                for(int i=0; i<4; i++){
                    for(int j=1; j<5; j++){
                        switch( map[i][j] ){
                            case 1:
                                if(map[i+1][j]==0 && map[i][j+1]==0 && map[i][j-1]==0){
                                    map[i][j]=0;
                                    flag=true;
                                    break;//注意!!
                                }
                                if(map[i+1][j] == 0){
                                    if( j < 3 ){
                                        map[i][j]=2;
                                    }else{
                                        map[i][j]=4;
                                    }
                                    flag=true;
                                }
                                break;
                            case 2:
                                if(map[i][j+1] == 0){
                                    if(map[i][j-1] == 0){
                                        map[i][j]=0;
                                    }else{
                                        map[i][j]=4;
                                    }
                                    flag=true;
                                }else if(map[i][j+1] == 4){
                                    if(map[i][j-1] == 0){
                                        map[i][j]=0;
                                    }else{
                                        map[i][j]=4;
                                    }
                                    flag=true;
                                }
                                break;
                            case 4:
                                if(map[i][j-1] == 0 ){
                                    if(map[i][j+1] == 0){
                                        map[i][j]=0;
                                    }else{
                                        map[i][j]=2;
                                    }
                                    flag=true;
                                }else if(map[i][j-1] == 2){
                                    if(map[i][j+1] == 0){
                                        map[i][j]=0;
                                    }else{
                                        map[i][j]=2;
                                    }
                                    flag=true;
                                }
                                break;
                            default:
                                break;
                        }//switch__end
                    }//for_end
                }//for_end
                            /*----------------------無限ループ確認用
                            lcd.clear();
                            for(int i=4; i>=0; i--){
                                for(int j=0; j<6; j++){
                                    lcd.putf("d",map_dummy[i][j],0);
                                }
                                lcd.putf("n");
                            }
                            lcd.disp();
                            ----------------------*/
            }//while_end
            /* ----------------------出力結果確認用
            lcd.clear();
            for(int i=4; i>=0; i--){
                for(int j=0; j<6; j++){
                    lcd.putf("d",map_dummy[i][j],0);
                }
                lcd.putf("n");
            }
            lcd.disp();

            while(true){
                clock.wait(10);
            }
            ----------------------*/
        }

        int Search_route(){ //sol_route ni route wo push siteikuyatu
            int i = 0;
            int j = 0;
            bool danger = false;
            if(1 == map[0][3]){ //decide start position
                start_pos = 3;
            }else if(1 == map[0][2]){
                start_pos = 2;
            }else if(1 == map[0][1]){
                start_pos = 1;
            }else if(1 == map[0][4]){
                start_pos = 4;
            }else{
                Retire(12345);
                return(1);
            }

            j = start_pos;
            while(5 != sol_route.back()){
                sol_route.push_back(0);
                sol_route.push_back(map[i][j]);
                switch( map[i][j] ){
                    case 1:
                        i++;
                        break;
                    case 2:
                        j++;
                        break;
                    case 4:
                        j--;
                        break;
                    case 0:
                        danger = true;
                        sol_route.push_back(5);
                        break;
                    default:
                        break;
                }
            }
            end_pos = j;

            if(danger){
                Retire(start_pos);
                return(1);
            }

            return(0);
        }

        void Set_position(int pos){
            int dis = 23;
            int ang = 310;
            if(2 == pos){
                dis += 23;
            }else if(3 == pos){
                dis += 49;
                ang = 270;
            }else if(4 == pos){
                dis += 72;
                ang = 250;
            }
	        Right_turn_2();
	        Left_turn_2(250);
	        pidrun.fix_position();
	        clock.wait(1500);
	        tra.move_pid(dis,true); //1...+0    2...+23    3...+48    4...+72
	        bar.fix_Direction(0);
	        Left_turn_2(ang);  //1...310   2...310    3...290    4...250
	        bar.fix_Direction(-10);
	        clock.wait(1000);
	        bar.ride_bord_kai(980);
	        clock.wait(1000);
        }

        void Path_trace(){ //9_18
            int distance=20;//今は適当な値を入れている
            //int test_date [] = {0, 1, 1, 2, 1, 0, 5};
            for(int i = 0; i != sol_route.size(); i++){
               //for(int i = 1; i < 7 ; i++){
                clock.sleep(1200);
                switch(sol_route[i]){
                    case 1:
                        switch(sol_route[i-1]){
                            case 1:
                                lcd.clear();
                                lcd.putf("sn","case1_1");
                                lcd.disp();
                                Go_straight(distance);
                            break;
                            case 2:
                                lcd.clear();
                                lcd.putf("sn","case1_2");
                                lcd.disp();
                                Left_turn3();
                                Go_straight(distance);
                            break;
                            case 4:
                                lcd.clear();
                                lcd.putf("sn","case1_4");
                                lcd.disp();

                                Right_turn3();
                                Go_straight(distance);
                            break;
                            default:
                                lcd.clear();
                                lcd.putf("sn","case1_de");
                                lcd.disp();

                                motorA.setPWM(10);
                                motorA.setPWM(-10);
                                Go_straight(distance);
                            break;

                        }
                        break;
                    case 2:
                        switch(sol_route[i-1]){
                            case 1:
                                lcd.clear();
                                lcd.putf("sn","case2_1");
                                lcd.disp();

                                Right_turn3();
                                Go_straight(10);
                                break;
                             case 2:
                                lcd.clear();
                                lcd.putf("sn","case2_2");
                                lcd.disp();

                                Go_straight(distance);
                                break;
                             case 4://本来ならありえない
                                lcd.clear();
                                lcd.putf("sn","case2_4");
                                lcd.disp();

                                //Go_straight(distance);
                                break;
                             default:
                                lcd.clear();
                                lcd.putf("sn","case2_de");
                                lcd.disp();
                                Right_turn3();
                                Go_straight(10);
                                //Go_straight(distance);
                                break;
                        }
                        break;
                    case 4:
                        switch(sol_route[i-1]){
                            case 1:
                                lcd.clear();
                                lcd.putf("sn","case4_1");
                                lcd.disp();

                                Left_turn3();
                                Go_straight(distance);
                                Go_straight(10);
                                break;
                             case 2://本来ならありえない
                                lcd.clear();
                                lcd.putf("sn","case4_2");
                                lcd.disp();

                                //Go_straight(distance);
                                break;
                             case 4:
                                lcd.clear();
                                lcd.putf("sn","case4_4");
                                lcd.disp();

                                Go_straight(distance);
                                break;
                             default:
                                lcd.clear();
                                lcd.putf("sn","case4_DE");
                                lcd.disp();
                                Left_turn3();
                                //Go_straight(distance);
                                break;
                        }
                        break;
                    case 5: //end
                        Go_straight(30);
                        while(true){
                        clock.wait(10);
                            lcd.clear();
                            lcd.putf("sn","case5_END");
                            lcd.disp();
                        }
                         break;
                    default:
                            lcd.clear();
                            lcd.putf("sn","case0_");
                            lcd.disp();

                        break;
                }

            }
        }

        void Return_line(){}

        void Retire(int hoge){
            motorA.setPWM(100);
            motorB.setPWM(0);
            motorC.setPWM(0);
            //Show_map(hoge);
            lcd.clear();
            lcd.putf("sn","hands up");
            lcd.disp();
            while(true){
                clock.wait(10);
            }
        }

        int Capture_unknown(vector<int> &temp){
            int call_retire = 0;

            call_retire = Check_barcode(temp);
            Make_map();
            Modify_map();
            call_retire += Search_route();
            if(0 != call_retire){
                Retire(1919);
                return(1);
            }
            Show_map(114514);
            clock.wait(1200);
            Show_map(987654321);
            clock.wait(200000000000);
            Set_position(start_pos);
            Path_trace();
            lcd.clear();
            Show_map(start_pos);
            lcd.putf("s","route:");
            for(int i = 0; i != sol_route.size(); i++){
                lcd.putf("d",sol_route[i],0);
            }
            lcd.disp();
            while(true){
                clock.wait(100);
            }
            while(true){
                pidrun.pid_running(true,0);
            }
        }

        void Right_turn(){
            dri.angle(680,80);
            dri.forward(290,80,0,0);
            par.reset(100);
        }

        void Right_turn_2(){
            dri.angle(580,80);
            dri.forward(250,80,0,0);
            par.reset(100);
        }
        void Right_turn3(){//33333333333333333333333
            dri.angle(670,80);//680,80 第一引数モータA角度
            dri.forward(270,80,0,0);//290,80,0,0 第一引数左モーター回転角
            par.reset(100);
            motorA.setPWM(-10);
        }

        void Left_turn(){
            dri.angle(-680,80);
            dri.forward(290,0,80,1);
            par.reset(100);
        }

        void Left_turn_2(int var){
            dri.angle(-680,80);
            dri.forward(var,0,80,1);
            par.reset(100);
        }
        void Left_turn3(){//33333333333333333333333
            dri.angle(-670,75);
            dri.forward(290,0,80,1);
            par.reset(100);
            motorA.setPWM(10);
        }


        void Go_straight(int distance){
            motorA.setPWM(5);
            motorA.setPWM(-5);
            tra.move(tra.moving_distance(distance));
        }

        void Show_map(int num){
            lcd.clear();
            for(int i=0; i<8; i++){
                lcd.putf("d",array[i],0);
            }
            lcd.putf("n");
            lcd.putf("dn",num,5);
            for(int i=4; i>=0; i--){
                for(int j=0; j<6; j++){
                    lcd.putf("d",map[i][j],0);
                }
                lcd.putf("n");
            }
            lcd.disp();
        }

    };
}