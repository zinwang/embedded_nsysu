#include <stdio.h>
#define u8 unsigned char
typedef union{
    float f;
    char bts[4];
}fu;



int main(){
    unsigned c,d,*b,g,E,S;
    unsigned long F;
    double x,t;
    g=2<<22;
    c=g-1;
    d=0b11111111;
    fu a;
    while(1){
        printf("input a float:");
        scanf("%f",&(a.f));
        b = &(a.bts);
    
        F=(*b)&c;
        E=((*b)>>23)&d;
        S=(*b)>>31;
        printf("S:%d\nF:%d\nE:%d\n",S,F,E);
   
    
        t=(F|g) << (E-127);  //t=(1*10^24+F)*2^(E-127)
        t=t/(2<<22);
        x=S?-t:t;
        printf("X:%.3f\n",x);
    
        printf("DEC:%u\n",*b);
        printf("HEX:%02hhx %02hhx %02hhx %02hhx\n\n",a.bts[3],a.bts[2],a.bts[1],a.bts[0]);
    }

    return 0;
}
