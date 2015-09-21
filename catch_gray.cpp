using namespace ecrobot;
extern "C"
{

class CatchGray{

	public:
	int catch_g(int now_light,int search,int threshold){
		if(now_light > threshold){
			search++;
		}else{
			search = 0;
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
