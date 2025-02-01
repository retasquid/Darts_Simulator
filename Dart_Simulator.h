#ifndef Dart_SimulatorH
#define Dart_SimulatorH
#include<iostream>
#include<math.h>
#include<ctime>
#include<SFML/Graphics.hpp>


const float grav=9.81*250;
const float pi=3.14159265;

float RadToDeg(float rad);
float DegToRad(float deg);
void delay(int t);

class lancer{
    public :
        lancer(short name){id = name;}
        void SetLaunch(float dist_cible, bool mode);
        void SetWind(float vent, float phiV, float alphaV);
        void SetScore(float x, float y);
        float Xt(float t);
        float Yt(float t);
        float Zt(float t);
        float Yx(float x);
        float Zx(float x);
        float GetTvol();
        int GetScore();
        short ID();
    private :
        short x0, y0, id;
        float alpha, phi;
        float vitesseX, vitesseY, vitesseZ, Tmp_vol;
        float ventX=0;
        float ventY=0;
        float ventZ=0;
        int score=501;
};

#endif