#include"Dart_Simulator.h"
#include"cible.h"
using std::cin, std::cout;

void lancer::SetLaunch(float dist_cible, bool mode){
    float Phi, Alpha, Yo, Xo;
    srand(time(nullptr));
    cout<<"##==============##\n";
    cout<<"##   Joueur "<<id<<"   ##\n";
    cout<<"##==============##\n\n";
    cout<<"A quelle vitesse avez vous lance : \n";
    cin>>vitesse;
    while(1){
        if(vitesse<=0){
            cout<<"saisisez un nombre positif :";
            cin>>vitesse;
        }else{
            break;
        }
    }
    cout<<"A quelle angle vertical avez vous lance : \n";
    cin>>Phi;
    if(mode){
        cout<<"A quelle angle horizontal avez vous lance : \n";
        cin>>Alpha;
        cout<<"A quelle distance de la ligne de lance avez vous lance : \n";
        cin>>Xo;
        x0=Xo*scale_1m_to_px;
    }else{
        Alpha=0;
        x0=0;
    }
    cout<<"A quelle hauteur initial avez vous lance : \n";
    cin>>Yo;
    y0=Yo*scale_1m_to_px;
    phi=DegToRad(Phi);
    alpha=DegToRad(Alpha);
    vitesseX=vitesse*cos(alpha)*cos(phi)*scale_1m_to_px;
    vitesseY=vitesse*cos(alpha)*sin(phi)*scale_1m_to_px;
    vitesseZ=vitesse*sin(alpha)*scale_1m_to_px;
    Tmp_vol=(dist_cible-x0)/vitesseX;
}
void lancer::SetWind(float vent, float phiV, float alphaV){
    float TMPa=DegToRad(alphaV);
    float TMPp=DegToRad(phiV);
    ventX=vent*cos(TMPa)*cos(TMPp);
    ventY=vent*cos(TMPa)*sin(TMPp);
    ventZ=vent*sin(TMPa);
}
float lancer::Xt(float t){
    return t*vitesseX+x0;
}
float lancer::Yt(float t){
    return t*vitesseY-(grav*t*t)/2+y0;
}
float lancer::Zt(float t){
    return t*vitesseZ;
}
float lancer::Yx(float x){
    return (x-x0)*tan(phi)-(grav*(x-x0)*(x-x0))/(2*(vitesseX*vitesseX))+y0;
}
float lancer::Zx(float x){
    return (tan(alpha)*(x-x0))/cos(phi);
}
float lancer::GetTvol(){
    return Tmp_vol;
}
bool lancer::SetScore(float x, float y){
    short tmp_score = probaScore()*points(module(x,y-1.73),arg(x,y-1.73));
    if(tmp_score<score){
        score-=tmp_score;
        return 0;}
    if(tmp_score==score){
        score-=tmp_score;
        return 1;}
    return 0;
}
int lancer::GetScore(){
    return score;
}
short lancer::ID(){
    return id;
}
int lancer::vitesseKm(){
    return ((vitesseX*3.6f)/scale_1m_to_px);
}
bool lancer::probaScore(){
    float xa=Xt(GetTvol()-0.01);
    float ya=Yt(GetTvol()-0.01);
    float xb=Xt(GetTvol());
    float yb=Yt(GetTvol());
    cout<<"Xa : "<<xa<<"Ya : "<<ya<<"Xb : "<<xb<<"Yb : "<<yb<<"\n";
    float prob=(rand() % 1001)/1000.00;
    cout<<"prob : "<<prob<<"\n";
    float Pangle=(xb-xa)/sqrt((yb-ya)*(yb-ya)+(xb-xa)*(xb-xa));
    cout<<"Pangle : "<<Pangle<<"\n";
    float Pvitesse=1-pow(2,-vitesse/5.00);
    cout<<"Pvitesse : "<<Pvitesse<<"\n";
    if(prob<(Pangle*Pvitesse))return 1;
    cout<<"\nVous avez rater votre tire \n";
    return 0;
}

float RadToDeg(float rad){
    return (rad*180)/pi;
}
float DegToRad(float deg){
    return (deg*pi)/180;
}
void delay(int t){
    std::time_t c_time = std::time(nullptr);
    while(std::time(nullptr)-c_time<t){
    }
}