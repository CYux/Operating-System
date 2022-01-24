#include "stdio.h"
#include "math.h"

int main(){
    double list[10] = {5.82, 6.55, 3.65, 4.89, 5.78, 6.98, 7.55, 8.58, 9.99, 10.16};
    double sum = 0, ave;
    int i;
    
    /*calcute sum of 10 numbers*/
    for(i = 0; i < 10; i++){
        sum+=sqrt(list[i]);
    }

    ave = sum/10;

    printf("The average of their square roots is %.2f\n",ave);

    return 0;
}
