#include <stdio.h>
#define u8 unsigned char


typedef union{
    float f;
    struct{
        unsigned F:23;
        unsigned E:8;
        unsigned S:1;
    };
}fu;



int main(){
    unsigned *b,g;
    double x,t;
    g=2<<22;
    fu a;
    while(1){
        printf("input a float:");
        scanf("%f",&(a.f));
        b = &(a.f);
    
        printf("%x\n",a.f);
        printf("S:%x\nF:%x\nE:%x\n",a.S,a.F,a.E);
   
    
        t=(a.F|g) << (a.E-127);  //t=(1*10^24+F)*2^(E-127)
        t=t/(2<<22);
        x=a.S?-t:t;
        printf("X:%.3f\n",x);
    
    }

    return 0;
}
