#include"Dart_Simulator.h"
#include"Dart_Simulator.cpp"
#include"cible.h"
#include"cible.cpp"
using std::cout, std::cin;
int main(){
    lancer j1;
    j1.SetLaunch(10,10000,DegToRad(0),0,0,0);
    cout<<"temps de vol : "<<j1.Tvol()<<"\n";
    for(float i=0;i<=j1.Tvol();i+=0.0001){
        cout<<"x : "<<i<<" y : "<<j1.Yx(i)<<"\n";
    }

}
