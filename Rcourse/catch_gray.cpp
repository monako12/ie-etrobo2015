using namespace ecrobot;
extern "C"
{

class CatchGray{

	public:
	int catch_g(int now_light,int search,int black,int gray){
		if(now_light < black+10){
			search = 0;
		}else{
			search++;
		}
		return(search);
	}

	int gray_count(int gcount,int search){
		if(search > gcount){
			gcount = search;
		}
		else{
			gcount = gcount;
		}
		return(gcount);
	}
};
}
