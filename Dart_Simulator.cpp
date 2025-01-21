#include"Dart_Simulator.h"


void lancer::SetLaunch(float distance, float vitesse, float phi, float alpha, short xo, short yo){
    x0=xo;
    y0=yo;
    distance_cible=distance;
    phi=phi;
    alpha=alpha;
    vitesseX=vitesse*cos(alpha)*cos(phi);
    vitesseY=vitesse*cos(alpha)*sin(phi);
    vitesseZ=vitesse*sin(alpha);
}
void lancer::SetWind(float vent, float phiV, float alphaV){
    ventX=vent*cos(alphaV)*cos(phiV);
    ventY=vent*cos(alphaV)*sin(phiV);
    ventZ=vent*sin(alphaV);
}
float lancer::Xt(float t){
    return t*vitesseX+x0;
}
float lancer::Yt(float t){
    return t*vitesseY-(g*t*t)/2+y0;
}
float lancer::Zt(float t){
    return t*vitesseZ;
}
float lancer::Yx(float x){
    return (x-x0)*tan(phi)-(g*(x-x0)*(x-x0))/(2*(vitesseX*vitesseX))+y0;
}
float lancer::Zx(float x){
    return (tan(alpha)*(x-x0))/cos(phi);
}
float lancer::Tvol(){
    return (distance_cible-x0)/vitesseX;
}

float RadToDeg(float rad){
    return (rad*180)/pi;
}
float DegToRad(float deg){
    return (deg*pi)/180;
}