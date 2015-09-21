using namespace ecrobot;
extern "C"
{
class CatchGray{

	public:
	int catch_g(int now_light,int gray_search,int g_threshold){
		if(now_light > g_threshold){
			gray_search++;
		}else{
			gray_search = 0;
		}
		return(gray_search);

	}

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

};
}
