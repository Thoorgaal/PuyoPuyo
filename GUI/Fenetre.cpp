#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include "../moteurLogique/partie.h"
#include <SFML/Graphics.hpp>
#include "../moteurLogique/rand.h"
#include "../moteurLogique/Joueur.h"
#include "../moteurLogique/terrain.h"
#include "Fenetre.hpp"
#include <chrono>
#include <thread>


sf::RectangleShape  Fenetre::dessinerPuyoP(float x, float y, int c){
    sf::RectangleShape piece(sf::Vector2f(wP, hP));
    piece.setOutlineThickness(0);
    if(c == getVCouleursD("couleursD::ROUGE")) {
            piece.setFillColor(sf::Color::Red);
        }else if(c == getVCouleursD("couleursD::BLEU")){
            piece.setFillColor(sf::Color::Blue);
        }else if(c == getVCouleursD("couleursD::JAUNE")){
            piece.setFillColor(sf::Color::Yellow);
        }else if(c == getVCouleursD("couleursD::MAGENTA")){
            piece.setFillColor(sf::Color::Magenta);
        }else if(c == getVCouleursD("couleursD::VERT")){
            piece.setFillColor(sf::Color::Green);
        }else if(c == getVCouleursD("couleursD::VIDE")){
            piece.setFillColor(sf::Color::White);
        }

        if(c != 0){
            piece.setOutlineColor(sf::Color(100,100,100));
            piece.setOutlineThickness(1);
        }
    piece.setPosition(sf::Vector2f(xT + x*wP, yT + y*hP));
    return piece;
}
void Fenetre::afficherGT(int score){
    window.clear();
    sf::Text t;
    std::string annonce = "Votre score est de " +std::to_string(score)+ " points.";
    t.setFont(font);
    t.setString(annonce);
    t.setCharacterSize(100);
    t.setFillColor(sf::Color::Black);
    t.setPosition(sf::Vector2f((xT+wT)/4 +200,yT/2-80));

    std::vector<std::vector<int>> grid = getGrid();
    //if(aE != grid){
    sf::RectangleShape fond(sf::Vector2f(desktop.width, desktop.height));
    sf::RectangleShape choix(sf::Vector2f(wT,hT/getDLO()));
    fond.setFillColor(sf::Color(211,211,211));
    sf::RectangleShape terrain(sf::Vector2f(wT,hT));
    terrain.setPosition(sf::Vector2f(xT,yT));
    terrain.setFillColor(sf::Color(0,0,0,0));
    terrain.setOutlineColor(sf::Color::Black);
    terrain.setOutlineThickness(1);
    choix.setPosition(sf::Vector2f(xT,yT));
    choix.setFillColor(sf::Color(0,0,0,0));
    choix.setOutlineThickness(4);
    choix.setOutlineColor(sf::Color::Black);
    window.clear();
    
    window.draw(fond);
    window.draw(terrain);
    window.draw(choix);
    for(size_t i = grid.size()-1; (i+1)>=1; i--){
        for(size_t j = 0; j<grid[i].size(); j++){
            /*if(aE[i][j]!=grid[i][j]){
                for(float k = 0; k<=1-G; k+=G){
                    window.draw(dessinerPuyoP((float) j,((float) i)-1+k,0));
                    window.draw(dessinerPuyoP((float)j,((float)i)-1+k+G,aE[i][j]));
                    window.display();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                }
            }else{*/
                window.draw(dessinerPuyoP((float) j, float(i), grid[i][j]));
            }
        }
        window.draw(t);
        window.display();
        
    //}
    

       
    /*}else{
        sf::RectangleShape fond(sf::Vector2f(desktop.width, desktop.height));
        fond.setFillColor(sf::Color::White);
        sf::RectangleShape terrain(sf::Vector2f(wT,hT));
        terrain.setPosition(sf::Vector2f(xT,yT));
        terrain.setFillColor(sf::Color(0,0,0,0));
        terrain.setOutlineColor(sf::Color::Black);
        terrain.setOutlineThickness(1);
        window.clear();
        window.draw(fond);
        window.draw(terrain);
        for(size_t i =0; i<grid.size(); i++){
            for(size_t j =0 ; j<grid[i].size(); j++){
                window.draw(dessinerPuyoP((float) j, (float) i, grid[i][j]));
            }
        }
        window.display();
         std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }*/
    
   
}
Fenetre::Fenetre(char* m)
{   
   bool estEcris = false;
     window.create(sf::VideoMode(desktop.width, desktop.height), "PuyoPuyo", sf::Style::Fullscreen);
    
    if(!font.loadFromFile("../PoliceE/police1.ttf")){
        std::cout << "Votre police n'a pas chargé";
    }
    while(window.isOpen()){
        
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed) window.close();
            else if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::Escape){
                    window.close();
                    exit(0);
                }
            }
            
        }

        if(!getD()){
            
            commencerPartie(m, this);
        }else if(!estEcris){
            sf::Text fin;
            int s = getScore();
            std::string annonce = "Vous avez fini avec " + std::to_string(getScore()) + " points.";
            fin.setFont(font);
            fin.setString(annonce);
            fin.setCharacterSize(200);
            fin.setFillColor(sf::Color::Black);
            fin.setPosition(sf::Vector2f(desktop.width/2,desktop.height/2));
            window.draw(fin);
        }
        
    }
    
    
}
bool Fenetre::action(Joueur j1){
    while(true){ 
        
        sf::Event e;
        
        while(window.pollEvent(e)){ 
                
            if (e.type == sf::Event::KeyPressed){
                
                switch(e.key.code){
                    
                    case sf::Keyboard::Z:
                    std::cout << "probleme";
                        
                                
                                j1.zSolo();

                                return true;
                        
                        
                        break;
                        case sf::Keyboard::S:
                                j1.sSolo();
                                return true;
                        break;
                        case sf::Keyboard::Q:
                                j1.qSolo();
                                return true;
                        break;
                        case sf::Keyboard::D:
                                j1.dSolo();
                                return true;
                        
                        break;
                        case sf::Keyboard::E:
                                return false;
                        
                        break;
                        case sf::Keyboard::Escape:
                            window.close();
                            return false;
                    }
                }
            }
        }
    
    return true;
}

