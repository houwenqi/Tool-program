#include <stdio.h>
#include <stdlib.h>
#include <math.h>    
    
const double x_pi = 3.14159265358979324 * 3000.0 / 180.0;    

void bd_encrypt(double gg_lat, double gg_lon, double &bd_lat, double &bd_lon)    
{    
    double x = gg_lon, y = gg_lat;    
    double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);    
    double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);    
    bd_lon = z * cos(theta) + 0.0065;    
    bd_lat = z * sin(theta) + 0.006;    
}    
    
void bd_decrypt(double bd_lat, double bd_lon, double &gg_lat, double &gg_lon)    
{    
    double x = bd_lon - 0.0065, y = bd_lat - 0.006;    
    double z = sqrt(x * x + y * y) - 0.00002 * sin(y * x_pi);    
    double theta = atan2(y, x) - 0.000003 * cos(x * x_pi);    
    gg_lon = z * cos(theta);    
    gg_lat = z * sin(theta);    
} 

int main()
{
  double gg_lat = 22.542847;
  double gg_lon = 113.950383;
  double bd_lat = 0.0;
  double bd_lon = 0.0;

  printf("gg_lat is %lf, gg_lon is %lf\n",gg_lat, gg_lon );

  bd_encrypt(gg_lat,gg_lon,bd_lat,bd_lon);

  printf("bd_lat is %lf, bd_lon is %lf\n",bd_lat, bd_lon );

  return 0;
}