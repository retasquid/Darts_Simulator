#include"cible.h"

//attribution des points de la cible en fonction de la position
int points(float p,float arg){
    int score;
    if(p<=0.00635){
        score=50;
    }else if(p>0.00635 and p<=0.0159){
        score=25;
    }else if(p>0.17){
        score=0;
    }else{
        if(arg>=-0.157 and arg < 0.157)score=6;
        if(arg>=0.157 and arg < 0.471)score=13;
        if(arg>=0.471 and arg < 0.785)score=4;
        if(arg>=0.785 and arg < 1.099)score=18;
        if(arg>=1.099 and arg < 1.413)score=1;
        if(arg>=1.413 and arg < 1.727)score=20;
        if(arg>=1.727 and arg < 2.041)score=5;
        if(arg>=2.041 and arg < 2.355)score=12;
        if(arg>=2.355 and arg < 2.669)score=9;
        if(arg>=2.669 and arg < 2.983)score=14;
        if((arg<-2.983 and arg > -3.2)||(arg>=2.983 and arg <3.2))score=11;
        if(arg<-0.157 and arg >= -0.471)score=8;
        if(arg<-0.471 and arg >= -0.785)score=16;
        if(arg<-0.785 and arg >= -1.099)score=7;
        if(arg<-1.099 and arg >= -1.413)score=19;
        if(arg<-1.413 and arg >= -1.727)score=3;
        if(arg<-1.727 and arg >= -2.041)score=17;
        if(arg<-2.041 and arg >= -2.355)score=2;
        if(arg<-2.355 and arg >= -2.669)score=15;
        if(arg<-2.669 and arg >= -2.983)score=10;
        if(p<=0.1074 and p>=0.0994){
            std::cout<<"point triple\n";
            score=score*3;
        }
        if(p<=0.17 and p>=0.162){
            score=score*2;
            std::cout<<"point double\n";
        }
    }
    return score;
}
//convertion en coordonées polaire
float module(float x, float y){
    return sqrt(x*x+y*y);
}
float arg(float x, float y){
    float m=module(x,y);
    if(m==0)return 0;
    if(y<0)return (-acos(x/m));
    if(y>=0)return (acos(x/m));
    return 0;
}