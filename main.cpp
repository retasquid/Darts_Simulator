#include"Dart_Simulator.h"
#include"Dart_Simulator.cpp"
#include"cible.h"
#include"cible.cpp"

using namespace std;
using namespace sf;

int main(){
    const bool mode = 0; //Mode 0 = simple; 1 = avancé
    unsigned int window_wide = 1920;
    unsigned int window_height = 1080;
    const float distance_cible = scale_1m_to_px*2.37f;
    const float x_cible_face = window_wide*0.85f;
    const float y_cible_face = window_height*0.2f;
    extern const unsigned short scale_1m_to_px;
    bool condition_victoire = 0;
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

    Text titre(font,"");
    titre.setPosition({10,10});
    titre.setFillColor(Color(0xFFFFFFA0));

    Text vitKm(font,"");
    titre.setPosition({10,30});
    titre.setFillColor(Color(0xFFFFFFA0));

    CircleShape flechette(10,100);
    flechette.setOrigin({10,10});
    flechette.setPosition({0,(float)window_height-10});
    flechette.setScale({1,0.5});

    Texture texture;
    if (!texture.loadFromFile("Cosmetics/cible.png"))cerr<<"Erreur de chargement de la cible.";

    CircleShape cible(scale_1m_to_px*0.225,50);
    cible.setOrigin({scale_1m_to_px*0.225f,scale_1m_to_px*0.225f});
    cible.setScale({0.8,1});
    cible.setTexture(&texture);
    cible.setPosition({distance_cible,(float)window_height-(scale_1m_to_px*1.73f)});

    CircleShape cibleface(225.5,50);
    cibleface.setOrigin({225.5,225.5});
    cibleface.setTexture(&texture);
    cibleface.setPosition({x_cible_face, y_cible_face});

    CircleShape flechetteface(10,30);
    flechetteface.setOrigin({10,10});
    flechetteface.setFillColor(Color(0x3E2F5B9F));
    flechetteface.setPosition({0,0});

    //Logo dart sim
    cout<<"\n\n#####    ####   #####   ######     ####   ######  ##   ##\n##  ##  ##  ##  ##  ##    ##      ##        ##    ### ###\n##  ##  ######  #####     ##       ####     ##    ## # ##\n##  ##  ##  ##  ##  ##    ##          ##    ##    ##   ##\n#####   ##  ##  ##  ##    ##       ####   ######  ##   ##\n\n\n";
    //demande distance cible
    cout<<"  ------------------------------------\n";
    cout<<"  La cible est a une distance de 2.37m\n";
    cout<<"  ------------------------------------\n";
    joueur.SetLaunch(distance_cible, mode);
    window->setVisible(1);
    joueur.SetScore(joueur.Zt(joueur.GetTvol())/scale_1m_to_px,joueur.Yt(joueur.GetTvol())/scale_1m_to_px);
    titre.setString("Appuillez sur (espace) pour lancer et sur (j) pour changer de joueur :\nScore du joueur : "+to_string(joueur.GetScore())+"pts");
    vitKm.setString("votre vitesse est de "+to_string(joueur.vitesseKm())+" km/h");
    cout<<"\nAppuillez sur (espace) pour lancer : \nAppuillez sur (j) pour changer de joueur :\n\n";
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
                        window->draw(vitKm);
                        window->draw(cibleface);
                        window->draw(flechetteface);
                        window->display();
                    }
                    flechetteface.setPosition({(x_cible_face+joueur.Zt(joueur.GetTvol())),(y_cible_face-joueur.Yt(joueur.GetTvol())+scale_1m_to_px*1.73f)});
                }
            }
            if(const auto* KeyPressed = event->getIf<Event::KeyPressed>()){
                if(KeyPressed->scancode==Keyboard::Scancode::J && !condition_victoire){
                    window->setVisible(0);
                    cout<<"\nchangement de joueur\n\n";
                    if(joueur.ID()==j1.ID()){
                        j1=joueur;
                        joueur=j2;
                    }else if(joueur.ID()==j2.ID()){
                        j2=joueur;
                        joueur=j1;
                    }
                    joueur.SetLaunch(distance_cible, mode);
                    window->setVisible(1);
                    condition_victoire = joueur.SetScore(joueur.Zt(joueur.GetTvol())/scale_1m_to_px,joueur.Yt(joueur.GetTvol())/scale_1m_to_px);
                    if(condition_victoire){
                        titre.setScale({1.5f,1.5f});
                        titre.setPosition({30,(float)(window_height/2)});
                        titre.setString("Le joueur "+to_string(joueur.ID())+" gagne la partie");
                    }else{
                        titre.setString("Appuyez sur (espace) pour lancer et sur (j) pour changer de joueur :\nScore du joueur "+to_string(joueur.ID())+" : "+to_string(joueur.GetScore())+"pts");
                        vitKm.setString("votre vitesse est de "+to_string(joueur.vitesseKm())+" km/h");
                    }
                }
            }
        }
        window->clear();
        window->draw(titre);
        window->draw(cible);
        window->draw(cibleface);
        window->draw(flechetteface);
        window->display();  
    }
}