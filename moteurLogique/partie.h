#ifndef PARTIE_H_INCLUDED
#define PARTIE_H_INCLUDED

#include <vector>
#include "../GUI/Fenetre.hpp"
#include "Joueur.h"
#include <fstream>
#include "Joueur.h"
// ce fichier fait en sorte que la partie se déroule dans l'ordre et dans le mode voulu en appelant 1 par une les méthodes nécéssaires
// au fonctionnement de la partie. C'est un peu la centrale ou une sorte de script

enum modeP{SOLO, INTA, SIMULATION,SOLOT}; 

void cleanP();
void compterScore(Joueur &j);
void setCoupWithPiece(char puyo1, char puyo2, Joueur j1);
bool goodFileIN ( std::ifstream & ifsIN, std::string & fileheader) ;    
void solo(Fenetre* fen);
void IA(Fenetre* fen);
void simulation(Fenetre* fen);
void soloT(Fenetre* fen);
void commencerPartie(char* inputFile, Fenetre* fen);
bool getD();
int getScore();
char* getFileIN();
int getScore();
#endif
	

