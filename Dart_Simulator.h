#ifndef Dart_SimulatorH
#define Dart_SimulatorH
#include<iostream>
#include<math.h>
#include<ctime>
#include<cstdlib>
#include<SFML/Graphics.hpp>

const unsigned short scale_1m_to_px = 450;
const float grav = 9.81*scale_1m_to_px;
const float pi = 3.14159265;


float RadToDeg(float rad);
float DegToRad(float deg);
void delay(int t);

class lancer{
    public :
        lancer(short name){id = name;}
        void SetLaunch(float dist_cible, bool mode);
        void SetWind(float vent, float phiV, float alphaV);
        bool SetScore(float x, float y);
        float Xt(float t);
        float Yt(float t);
        float Zt(float t);
        float Yx(float x);
        float Zx(float x);
        float GetTvol();
        int GetScore();
        short ID();
        int vitesseKm();
        bool probaScore();
    private :
        short x0, y0, id;
        float alpha, phi;
        float vitesse, vitesseX, vitesseY, vitesseZ, Tmp_vol;
        float ventX=0;
        float ventY=0;
        float ventZ=0;
        int score=100;
};

#endif