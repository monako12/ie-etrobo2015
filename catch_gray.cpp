using namespace ecrobot;
extern "C"
{
class CatchGray{

	public:
	int catch_g(int now_light,int gray_search,int threshold,int white){
		if(now_light >= threshold && now_light < white){
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
