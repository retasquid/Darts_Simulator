//         _______________________________________________________________
//        /                                                               \
//        |   #####    ####   #####   ######     ####   ######  ##   ##   |
//        |   ##  ##  ##  ##  ##  ##    ##      ##        ##    ### ###   |
//        |   ##  ##  ######  #####     ##       ####     ##    ## # ##   |
//        |   ##  ##  ##  ##  ##  ##    ##          ##    ##    ##   ##   |
//        |   #####   ##  ##  ##  ##    ##       ####   ######  ##   ##   |
//        \_______________________________________________________________/
//
//           @author : Noé Dargaud
//           @date   : 2025
//           @brief  : simulateur de cible 3d avec vent
//

#include"Dart_Simulator.h"
#include"Dart_Simulator.cpp"
#include"cible.h"
#include"cible.cpp"

using namespace std;
using namespace sf;

int main(){
    const unsigned short window_wide = 1920;
    const unsigned short window_height = 1080;
    const float x_cible_face = window_wide*0.85f;
    const float y_cible_face = window_height*0.2f;
    extern const unsigned short scale_1m_to_px;
    bool condition_victoire = 0;
    extern short vitVent, alphaVent, phiVent, mode_jeux;

    lancer j1(1);
    lancer j2(2);
    lancer joueur = j1;

    // Création de la fenetre
    RenderWindow* window= new RenderWindow(VideoMode({window_wide,window_height}),"Dart Simulator");
    window->setFramerateLimit(60);
    window->setVisible(0);

    // Chargement de l'icone d'application 
    Image icon;
    if (!icon.loadFromFile("Cosmetics/Dart_Simulator.png"))cerr<<"Erreur de chargement de l'icone.";
    window->setIcon(icon.getSize(),icon.getPixelsPtr());

    // Chargement de la police 
    Font font;
    if(!font.openFromFile("Cosmetics/Nunito-Bold.ttf"))cerr<<"Erreur de chargement des polices.";

    // Création du texte d'indication et de score 
    Text titre(font,"");
    titre.setPosition({10,10});
    titre.setFillColor(Color(0xFFFFFFA0));

    // Création du text de la vitesse en km/h 
    Text vitKm(font,"");
    titre.setPosition({10,30});
    titre.setFillColor(Color(0xFFFFFFA0));

    // Création de la fléchette 
    CircleShape flechette(10,100);
    flechette.setOrigin({10,10});
    flechette.setPosition({0,(float)window_height-10});
    flechette.setScale({1,0.5});

    // Chargement de la texture cible 
    Texture texture1;
    if (!texture1.loadFromFile("Cosmetics/cible.png"))cerr<<"Erreur de chargement de la cible.";

    // Création de la cible principale 
    CircleShape cible(scale_1m_to_px*0.225,50);
    cible.setOrigin({scale_1m_to_px*0.225f,scale_1m_to_px*0.225f});
    cible.setScale({0.8,1});
    cible.setTexture(&texture1);
    cible.setPosition({scale_1m_to_px*2.37f,(float)window_height-(scale_1m_to_px*1.73f)});

    // Création de la cible d'indication
    CircleShape cibleface(225.5,50);
    cibleface.setOrigin({225.5,225.5});
    cibleface.setTexture(&texture1);
    cibleface.setScale({0.5,0.5});
    cibleface.setPosition({x_cible_face, y_cible_face});

    // Création de la flechette d'indication
    CircleShape flechetteface(10,30);
    flechetteface.setOrigin({10,10});
    flechetteface.setFillColor(Color(0x3E2F5B9F));
    flechetteface.setPosition({0,0});

    //Création de l'indicateur de vitesse de vent
    RectangleShape wind({100,200});
    wind.setOrigin({0,0});
    wind.setPosition({x_cible_face,(float)window_height-100});
    wind.setRotation(degrees(180));

    //demande distance cible
    SetParameter();
    joueur.SetLaunch();

    //parametrage du vent
    joueur.SetWind();
    j2.SetWind();
    if(vitVent<=8){
        wind.setFillColor(Color(0x23ff00ff));
    }else if(vitVent<=16){
        wind.setFillColor(Color(0xffb200ff));
    }else{
        wind.setFillColor(Color(0xff4200ff));
    }
    wind.setScale({1,(vitVent/24.f)});
    //affichage de la simulation graphique
    window->setVisible(1);
    joueur.SetScore(joueur.Zt(joueur.GetTvol())/scale_1m_to_px,joueur.Yt(joueur.GetTvol())/scale_1m_to_px);
    titre.setString("Appuillez sur (espace) pour lancer et sur (j) pour changer de joueur :\nScore du joueur : "+to_string(joueur.GetScore())+"pts");
    vitKm.setString("votre vitesse est de "+to_string(joueur.vitesseKm())+" km/h");

    while(window->isOpen()){
        while(const optional event = window->pollEvent()){
            //fermeture si la croix est cliqué
            if(event->is<Event::Closed>())window->close();
            //lancé de la fléchette avec espace
            if(const auto* KeyPressed = event->getIf<Event::KeyPressed>()){
                if(KeyPressed->scancode==Keyboard::Scancode::Space){
                    //boucle d'affichage des position intermediaire de la fléchette
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
                    //definition de la position de la fléchette de face
                    flechetteface.setPosition({(x_cible_face-joueur.Zt(joueur.GetTvol())),(y_cible_face-joueur.Yt(joueur.GetTvol())+scale_1m_to_px*1.73f)});
                }
            }
            //changement de joueur avec j
            if(const auto* KeyPressed = event->getIf<Event::KeyPressed>()){
                if(KeyPressed->scancode==Keyboard::Scancode::J && !condition_victoire){
                    window->setVisible(0);
                    //invertion des joueurs
                    if(joueur.ID()==j1.ID()){
                        j1=joueur;
                        joueur=j2;
                    }else if(joueur.ID()==j2.ID()){
                        j2=joueur;
                        joueur=j1;
                    }
                    //demandes des infos du lancé
                    joueur.SetLaunch();
                    window->setVisible(1);
                    //vérification des conditions de victoires
                    condition_victoire = joueur.SetScore(joueur.Zt(joueur.GetTvol())/scale_1m_to_px,joueur.Yt(joueur.GetTvol())/scale_1m_to_px);
                    if(condition_victoire){
                        //écran de victoire
                        titre.setScale({1.5f,1.5f});
                        titre.setPosition({30,(float)(window_height/2)});
                        titre.setString("Le joueur "+to_string(joueur.ID())+" gagne la partie");
                    }else{
                        //joueur suivant
                        titre.setString("Appuyez sur (espace) pour lancer et sur (j) pour changer de joueur :\nScore du joueur "+to_string(joueur.ID())+" : "+to_string(joueur.GetScore())+"pts");
                        vitKm.setString("votre vitesse est de "+to_string(joueur.vitesseKm())+" km/h");
                    }
                }
            }

        }
        //affichage des élements graphiques
        window->clear();
        //affichage du vent si mode vent choisis
        if(mode_jeux==1 || mode_jeux==3 || mode_jeux==4)window->draw(wind);
        window->draw(titre);
        window->draw(cible);
        window->draw(cibleface);
        window->draw(flechetteface);
        window->display();
    }
}