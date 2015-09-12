using namespace ecrobot;
extern "C"
{
        SensorGet sens;
	int bw_ava = sens.ret_avarage();
	int l_gray = sens.ret_gray();
class CatchGray{

	public:
	int search_inc(int gray_search){
		gray_search++;
		return(gray_search);
	}

	int count_inc(int gray_count){
		gray_count++;
		return(gray_count);
	}

	int search_reset(int gray_search){
		gray_search = 0;
		return(gray_search);
	}

	int catch_g(int now_light){
		int check_g;
		if(l_gray > bw_ava){
			check_g = now_light - bw_ava;
		}else{
			check_g = now_light - l_gray;
		}
		return(check_g);
	}
};
}
