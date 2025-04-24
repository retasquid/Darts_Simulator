#include"Dart_Simulator.h"
#include"cible.h"
using std::cin, std::cout;

void SetParameter(){
    extern short mode_jeux;
    extern short vitVent, alphaVent, phiVent;
    srand(time(nullptr));
    /* LOGO DART SIM */
    cout<<"\n\n#####    ####   #####   ######     ####   ######  ##   ##\n##  ##  ##  ##  ##  ##    ##      ##        ##    ### ###\n##  ##  ######  #####     ##       ####     ##    ## # ##\n##  ##  ##  ##  ##  ##    ##          ##    ##    ##   ##\n#####   ##  ##  ##  ##    ##       ####   ######  ##   ##\n\n\n";
    
    cout<<"  ------------------------------------\n";
    cout<<"  La cible est a une distance de 2.37m\n";
    cout<<"   et elle est a une hauteur de 1.73m \n";
    cout<<"  ------------------------------------\n\n";

    cout<<"  ------------------------------------\n";
    cout<<"  Mode 0 : cible en 2D sans vent      \n";
    cout<<"  Mode 1 : cible en 2D avec vent      \n";
    cout<<"  Mode 2 : cible en 3D sans vent      \n";
    cout<<"  Mode 3 : cible en 3D avec vent      \n";
    cout<<"  Mode 4 : cible en 3D avec vent fort \n";
    cout<<"  ------------------------------------\n";
    //verificattion de saisie
    while(mode_jeux>4 || mode_jeux<0){
        cout<<"  > Choisisez votre mode : ";
        cin>>mode_jeux;
    }
    //configuration du vent selon le mode
    switch (mode_jeux){
    case 0 :
        vitVent = 0;
        alphaVent = 0;
        phiVent = 0;
        return;
    
    case 1 :
        vitVent = rand()%25;
        alphaVent = (rand()%361)-180;
        phiVent =  180-(rand()%361);
        cout<<"Le vent souffle a "<<vitVent*3.6<<" km/h aux angles alpha : "<<alphaVent<<"° et phi : "<<phiVent<<"°.\n";     
        return;
    
    case 2 :
        vitVent = 0;
        alphaVent = 0;
        phiVent = 0;
        return;
    
    case 3 :
        vitVent = rand()%25;
        alphaVent = (rand()%361)-180;
        phiVent = 180-(rand()%361);
        cout<<"Le vent souffle a "<<vitVent*3.6<<" km/h aux angles alpha : "<<alphaVent<<"° et phi : "<<phiVent<<"°.\n";
        return;
    
    case 4 :
        vitVent = rand()%41;
        alphaVent = (rand()%361)-180;
        phiVent = 180-(rand()%361);
        cout<<"Le vent souffle a "<<vitVent*3.6<<" km/h aux angles alpha : "<<alphaVent<<"° et phi : "<<phiVent<<"°.\n";      
        return;
    
    default:
        vitVent = 0;
        alphaVent = 0;
        phiVent = 0;
        return;
    }
}

void lancer::SetLaunch(){
    extern short mode_jeux;
    static float Phi, Alpha, Yo, Xo;
    static const float dist_cible = scale_1m_to_px*2.37f;
    cout<<"  ______________\n";
    cout<<" /              \\ \n";
    cout<<"|    Joueur "<<id<<"    |\n";
    cout<<" \\______________/\n\n";
    cout<<"A quelle vitesse avez vous lance (m/s) : \n";
    cin>>vitesse;
    while(1){
        if(vitesse<=0){
            cout<<"Saisisez un nombre positif :";
            cin>>vitesse;
        }else{
            break;
        }
    }
    cout<<"A quelle angle vertical avez vous lance (deg) : \n";
    cin>>Phi;
    if(mode_jeux==2 || mode_jeux==3 || mode_jeux==4){
        cout<<"A quelle angle horizontal avez vous lance (deg) : \n";
        cin>>Alpha;
        cout<<"A quelle distance de la ligne de lance avez vous lance (m) : \n";
        cin>>Xo;
        x0=Xo*scale_1m_to_px;
    }else{
        Alpha=0;
        x0=0;
    }
    cout<<"A quelle hauteur initiale avez vous lance (m) : \n";
    cin>>Yo;
    y0=Yo*scale_1m_to_px;
    phi=DegToRad(Phi);
    alpha=DegToRad(Alpha);
    vitesseX=vitesse*cos(alpha)*cos(phi)*scale_1m_to_px;
    vitesseY=vitesse*cos(alpha)*sin(phi)*scale_1m_to_px;
    vitesseZ=vitesse*sin(alpha)*scale_1m_to_px;
    Tmp_vol=(dist_cible-x0)/vitesseX;
}
void lancer::SetWind(){
    extern short vitVent, alphaVent, phiVent;
    float TMPa=DegToRad(alphaVent);
    float TMPp=DegToRad(phiVent);
    ventX=(K*vitVent*vitVent*cos(TMPa)*cos(TMPp)*scale_1m_to_px)/(2*0.02);
    ventY=(K*vitVent*vitVent*cos(TMPa)*sin(TMPp)*scale_1m_to_px)/(2*0.02);
    ventZ=(K*vitVent*vitVent*sin(TMPp)*scale_1m_to_px)/(2*0.02);
}
float lancer::Xt(float t){
    return t*vitesseX+x0+ventX*t*t;
}
float lancer::Yt(float t){
    return t*vitesseY-(grav*t*t)/2+y0-ventY*t*t;
}
float lancer::Zt(float t){
    return t*vitesseZ+ventZ*t*t;
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
    short tmp_score = probaScore()*points(module(x,y-1.73),arg(x,y-1.73)); //Test de la chance de planter
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
    float xa=Xt(GetTvol()-0.01);    //Génération des coordonées proche de la cible
    float ya=Yt(GetTvol()-0.01);    //pour connaitre l'angle d'arrivée
    float xb=Xt(GetTvol());
    float yb=Yt(GetTvol());
    float prob=(rand() % 1001)/1000.00; //Création de la chance entre 0 et 1 à 3 chiffres significatifs
    float Pangle=(xb-xa)/sqrt((yb-ya)*(yb-ya)+(xb-xa)*(xb-xa));
    float Pvitesse=1-pow(2,-vitesse/5.00);
    if(prob<(Pangle*Pvitesse))return 1;     //test des 2 probabilitées cumulées
    return 0;
}

float RadToDeg(float rad){
    return (rad*180)/pi;        //convertion radian vers degré
}
float DegToRad(float deg){
    return (deg*pi)/180;        //convertion degré vers radian
}