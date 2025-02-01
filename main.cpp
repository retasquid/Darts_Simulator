#include"Dart_Simulator.h"
#include"Dart_Simulator.cpp"
#include"cible.h"
#include"cible.cpp"

using namespace std;
using namespace sf;

int main(){
    bool mode = 0; //Mode 0 = simple; 1 = avancé
    unsigned int window_wide = 1500;
    unsigned int window_height = 750;
    float distance_cible;
    //1m=250px 

    lancer j1(1);
    lancer j2(2);
    lancer joueur = j1;

    RenderWindow* window= new RenderWindow(VideoMode({window_wide,window_height}),"Dart Simulator");
    window->setFramerateLimit(60);
    window->setVisible(0);

    Image icon;
    if (!icon.loadFromFile("Cosmetics/Dart_Simulator.png"))cerr<<"Erreur de chargement de l'icone.";
    window->setIcon(icon.getSize(),icon.getPixelsPtr());

    Font font;
    if(!font.openFromFile("Cosmetics/Nunito-Bold.ttf"))cerr<<"Erreur de chargement des polices.";

    Text titre(font);
    titre.setString("");
    titre.setPosition({10,10});
    titre.setFillColor(Color(0xFFFFFFA0));
    
    CircleShape flechette(10.f,100);
    flechette.setOrigin({10,10});
    flechette.setPosition({0,(float)window_height-10});
    flechette.setScale({1,0.5});

    Texture texture;
    if (!texture.loadFromFile("Cosmetics/cible.png"))cerr<<"Erreur de chargement de la cible.";

    CircleShape cible(42.5);
    cible.setOrigin({42.5,42.5});
    cible.setPointCount(50);
    cible.setScale({0.8,1});
    cible.setTexture(&texture);

    //Logo dart sim
    cout<<"\n\n#####    ####   #####   ######     ####   ######  ##   ##\n##  ##  ##  ##  ##  ##    ##      ##        ##    ### ###\n##  ##  ######  #####     ##       ####     ##    ## # ##\n##  ##  ##  ##  ##  ##    ##          ##    ##    ##   ##\n#####   ##  ##  ##  ##    ##       ####   ######  ##   ##\n\n\n";
    //demande distance cible
    cout<<"A quelle distance est la cible(m) : ";
    cin>>distance_cible;
    distance_cible*=250;
    float y_cible=(float)window_height-432.5;
    cible.setPosition({distance_cible,y_cible});
    
    joueur.SetLaunch(distance_cible, mode);
    window->setVisible(1);
    joueur.SetScore(joueur.Zt(joueur.GetTvol())/2.5,joueur.Yt(joueur.GetTvol())/2.5);
    cout<<"x : "<<(joueur.Zt(joueur.GetTvol()))*0.004<<"y : "<<(joueur.Yt(joueur.GetTvol()))*0.004;
    titre.setString("Score du joueur : "+to_string(joueur.GetScore())+"pts");

    cout<<"\nAppuillez sur (espace) pour lancer : \nAppuillez sur (j) pour changer de joueur :\n";
    while(window->isOpen()){
        while(const optional event = window->pollEvent()){
            if(event->is<Event::Closed>()){
                window->close();
            }
            if(const auto* KeyPressed = event->getIf<Event::KeyPressed>()){
                if(KeyPressed->scancode==Keyboard::Scancode::Space){
                    for(float step=0;step<=joueur.GetTvol();step+=joueur.GetTvol()/100){
                        window->clear();
                        flechette.setPosition({joueur.Xt(step),(window_height-joueur.Yt(step))});
                        window->draw(cible);
                        window->draw(flechette);
                        window->display();
                    }
                } 
            }
            if(const auto* KeyPressed = event->getIf<Event::KeyPressed>()){
                if(KeyPressed->scancode==Keyboard::Scancode::J){
                    window->setVisible(0);
                    cout<<"changement de joueur\n\n";
                    if(joueur.ID()==j1.ID()){
                        joueur=j2;
                    }else if(joueur.ID()==j2.ID()){
                        joueur=j1;
                    }
                    joueur.SetLaunch(distance_cible, mode);
                    window->setVisible(1);
                    joueur.SetScore(joueur.Zt(joueur.GetTvol())/2.5,joueur.Yt(joueur.GetTvol())/2.5);
                    cout<<"x : "<<(joueur.Zt(joueur.GetTvol()))*0.004<<"y : "<<(joueur.Yt(joueur.GetTvol()))*0.004;
                    titre.setString("Score du joueur "+to_string(joueur.ID())+" : "+to_string(joueur.GetScore())+"pts");
                    }
            }
        }
        window->clear();
        window->draw(titre);
        window->draw(cible);
        window->display();  
    }        
}