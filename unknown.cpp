extern "C"
{
    Barcode bar;
    Parking par;

    class Unknown{
        public:
            int map[5][6];
            int start_pos[2];
            int array[8];
        void Check_barcode(vector<int> &temp){
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
                while(true){
                    clock.wait(100);
                }

            }

            lcd.putf("sn","hoge");
            for(int i=0; i < 8; i++){
                array[i] = temp[i];
            }
            for(int i=0; i < 9; i++){
                if(i%2 == 0){
                    lcd.putf("d",array[i],0);
                }else{
                    lcd.putf("dn",array[i],1);
                }
            }
            lcd.disp();
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

            //Show_map(114514);
        }

        void Show_map(int num){
            lcd.clear();
            lcd.putf("dn",num,5);
            for(int i=4; i>=0; i--){
                for(int j=0; j<6; j++){
                    lcd.putf("d",map[i][j],0);
                }
                    lcd.putf("n");
            }
            lcd.putf("n");

            for(int i=0; i<8; i++){
                lcd.putf("d",array[i],0);
            }
            lcd.disp();
        }

        void Modify_map(){
            bool flag=true;//初期状態動作のためflag=1
            
            while(flag){
                flag = false;
                for(int i=0; i<4; i++){
                    for(int j=1; j<5; j++){
                        switch( map[i][j] ){
                            case 1: 
                                if( map[i+1][j] = 0){
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
                                if( map[i][j+1] = 0){
                                    map[i][j]=0;
                                    flag=true;
                                }else if(map[i][j+1] = 4){
                                    map[i][j]=4;
                                    flag=true;
                                }
                                break;
                            case 4:
                                if( map[i][j-1] = 0 ){
                                    map[i][j]=0;
                                    flag=true;
                                }
                                break;

                            default:
                                break;
                        }//switch__end
                    }//for_end
                }//for_end
            }//while_end
            Show_map(5555);
        }

        void Set_position(){
            map[0][1] = 0;
            map[0][2] = 1;
            map[0][3] = 0;
            map[0][4] = 1;


        }

        void Path_trace(){}

        void Return_line(){}

        void Retire(){}

        void Capture_unknown(vector<int> &temp){
            //Check_barcode(temp);
            //Make_map();
            //Right_turn();
            Left_turn();
           //Modify_map();
           //Show_map(364364);
            while(true){
                clock.wait(100);
            }
        }

        void Right_turn(){
            par.angle(680,100);
            par.forward(290,80,0,0);
            par.reset(100);
        }

        void Left_turn(){
            par.angle(-680,100);
            par.forward(290,0,80,1);
            par.reset(100);
        }
    };
}