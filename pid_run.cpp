
using namespace ecrobot;

extern "C"
{
	sensor sen;
	Cal calcu;
	Drive drive;

int ava = sen.lightavarage();

	class PIDrun{
		public:
		int pid_running(bool hoge){
			int nowl = sen.nowlight(ava);
			int ret_pid = calcu.cur_ava(nowl,ava);
			int sum = sen.ret_sum();
			int pos = drive.position();
			int line = calcu.cur_ava(nowl,ava);

			if(hoge == true){
				drive.mode_Black_Right(ret_pid,line);/*左側のエッジ(黒の左側)を走る*/
			}
			else{
				drive.mode_Black_Left(ret_pid,line);/*右側のエッジ(黒の右側)を走る*/
			}
			lcd.clear();
			lcd.putf("dn",pos);
			lcd.putf("d", ret_pid);
			lcd.disp();
		}

	};
}
