#include <math.h>
/* calculates the average of the sum of an array of 10 numbers */
int main(){
  double array[10] = {1.0, 2.0, 3.0, 4.0, 5.0, 10.2, 11.5, 12.6, 13.9, 14.7};
  double ave = 0;
  int i;
  for (i = 0; i < 10; i++){
    ave += sqrt(array[i]);
  }
  return 0;
}

