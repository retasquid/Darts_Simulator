#ifndef Dart_SimulatorH
#define Dart_SimulatorH
#include<iostream>
#include<math.h>
#include<ctime>
#include<cstdlib>
#include<SFML/Graphics.hpp>


const unsigned short scale_1m_to_px = 450;  //échelle de pixel pour 1metre
const float grav = 9.81*scale_1m_to_px; //constante de gravitation
const float pi = 3.14159265;
const float K = 0.0003;     //constante de la force du vent
short mode_jeux = 5;
short vitVent, alphaVent, phiVent;

float RadToDeg(float rad);
float DegToRad(float deg);
void SetParameter();

class lancer{
    public :
        lancer(short name){id = name;}
        void SetLaunch();
        void SetWind();
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
        float alpha, phi, Valpha, Vphi;
        float vitesse, vitesseX, vitesseY, vitesseZ, Tmp_vol;
        float ventX=0;
        float ventY=0;
        float ventZ=0;
        int score=501;
};

#endif