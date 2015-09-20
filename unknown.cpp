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

        void Modify_map(){
            bool flag=true;//初期状態動作のためflag=1
            
            while(flag){
                flag = false;
                for(int i=0; i<4; i++){
                    for(int j=1; j<5; j++){
                        switch( map[i][j] ){
                            case 1:
                                if(map[i+1][j]==0 && map[i][j+1]==0 && map[i][j-1]==0){
                                    map[i][j]=0;//上左右0の場合は0 9/11
                                    flag=true;
                                }
                                if(map[i+1][j] == 0){
                                    if( j < 3 ){
                                        map[i][j]=2;
                                    }
                                    else{
                                        map[i][j]=4;
                                    }
                                    flag=true;
                                }
                                break;
                            case 2:
                                if(map[i][j+1] == 0){
                                    map[i][j]=4;//修正箇所9/11
                                    flag=true;
                                }
                                else if(map[i][j+1] == 4){
                                    if(map[i][j-1] == 0){//修正箇所9/13
                                        map[i][j]=0;
                                    }
                                    else{
                                        map[i][j]=4;
                                    }
                                flag=true;
                                }
                                break;
                            case 4:
                                if(map[i][j-1] == 0 ){
                                    map[i][j]=2;//修正箇所9/11
                                    flag=true;
                                }
                                else if(map[i][j-1] == 2){
                                    if(map[i][j+1] == 0){//修正箇所9/13
                                        map[i][j]=0;
                                    }
                                    else{
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
            }//while_end
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

            if(danger){
                Retire(start_pos);
                return(1);
            }

            return(0);
        }

        void Set_position(){
            map[0][1] = 0;
            map[0][2] = 1;
            map[0][3] = 0;
            map[0][4] = 1;

            bar.search_bord(16);
            bar.fix_Direction(0);
            motorB.setPWM(30);
            motorC.setPWM(30);
            clock.wait(800);
            bar.fix_Direction(0);
            motorB.setPWM(0);
            motorC.setPWM(0);
            dri.angle(680,100);
            dri.forward(90,80,0,0);
            par.reset(100);
            Go_straight(DISTANCE/2);

        }

        void Path_trace(){
            int distance=20;//今は適当な値を入れている
            int test_date [] = {1, 2, 1, 4, 5};
            //for(int i = 0; i != sol_route.size(); i++){
              for(int i = 0; i < 5 ; i++){
                switch(test_date[i]){
                    case 1:

                        Go_straight(distance);
                        break;
                    case 2:
                        Right_turn();
                        Go_straight(distance);
                        break;
                    case 4:
                        Left_turn();
                        Go_straight(distance);
                        break;
                    case 5: //end
                    
                         break;
                    default:
                        break;
                }
            }
            while(true){
                clock.wait(10);
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
/*            int call_retire = 0;

            call_retire = Check_barcode(temp);
            Make_map();
            Modify_map();
            call_retire += Search_route();
            if(0 != call_retire){
                Retire(1919);
                return(1);
            }
            //Set_position();
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
            }*/
            //Set_position();
            while(true){
                pidrun.pid_running(false);
            }
        }

        void Right_turn(){
            dri.angle(680,100);
            dri.forward(290,80,0,0);
            par.reset(100);
        }

        void Left_turn(){
            dri.angle(-680,100);
            dri.forward(290,0,80,1);
            par.reset(100);
        }

        void Go_straight(int distance){
            motorA.setPWM(0);
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