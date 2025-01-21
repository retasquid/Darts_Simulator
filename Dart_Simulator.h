#ifndef Dart_SimulatorH
#define Dart_SimulatorH
#include<iostream>
#include<math.h>
#define g 9.81
#define pi 3.14159265

class lancer{
    public :
        void SetLaunch(float distance, float vitesse, float phi, float alpha, short xo, short yo);
        void SetWind(float vent, float phiV, float alphaV);
        float Xt(float t);
        float Yt(float t);
        float Zt(float t);
        float Yx(float x);
        float Zx(float x);
        float Tvol();
    private :
        short x0,y0;
        float distance_cible, alpha, phi, vitesseX, vitesseY, vitesseZ;
        float ventX=0;
        float ventY=0;
        float ventZ=0;
};

float RadToDeg(float rad);
float DegToRad(float deg);

#endif