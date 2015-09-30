using namespace ecrobot;
extern "C"
{
  double p_coe = 0.38;
  double i_coe = 0.06;
  double d_coe = 0.57;
  class Cal{
  public:
    int p_i_d(int ava,double cur){
      double p;
      double i;
      double d;
      double delta_t = 5;
      double diff[3] = {};
      double integral = 0;
      diff[0] = diff[1];
      diff[1] = cur - ava;
      integral += (diff[1] + diff[0])/2*delta_t;

      p = p_coe*diff[1];
      i = i_coe*integral;
      d = d_coe*(diff[1]-diff[0])/delta_t;
      cur = p + i + d;

      if(cur > 100) cur = 100;
      if(cur < -100) cur = -100;

      return (int)cur;
    }

    int cur_ava(int cur, double ava){
      int ret;
      ret = cur - ava;
      return(ret);
    }

    int send_i_value(int ava,double cur){
      int i;
      double delta_t = 5;
      double diff[3] = {};
      double integral = 0;
      diff[0] = diff[1];
      diff[1] = cur - ava;
      integral += (diff[1] + diff[0])/2*delta_t;
      i = i_coe*integral;
      return(i);
    }

  };

}
