#include <fstream>
#include "PuyoP.hpp"
#include "Joueur.h"
#include "terrain.h"
using namespace std;

bool testDefaite(PuyoP p) {
/** cette fonction verifie si il n y a pas de defaite
 * confiance = 100% : a toujours fonctionne et ne bog pas
 * par Ines **/
	int casesVideCount=0;
	for(int i =1; i< p.gridPuyo.size(); i++){
        	for(int j = 0; j<p.gridPuyo[i].size(); j++){
			if (p.gridPuyo[i][j] == p.couleursD::VIDE){
				casesVideCount++;
				if (casesVideCount >= 2) return false;
			}
		}
	}
	return true;
}
int grilleFinale( int score ) {
/** le but de cette fonction est d ecrire dans un fichier la grille finale du jeu lorsque celui ci se termine
confiance : 100% = cette fonction a ete teste de nombreuses fois et ecrit toujours la grille, peu importe le mode
par Ines**/
	PuyoP p = getPuyoP();
	ofstream fichierResultat;
	fichierResultat.open("REGLE2sortie.txt", ios::out); //on ouvre le fichier en ecriture
	if (fichierResultat.bad()) //permet de tester si le fichier s'est ouvert sans probleme
		return -1;
	if (testDefaite(p)) // On signale la défaite avant la grille et le score
		fichierResultat <<"DEFAITE" << endl;
// On écrit la grille finale
	for(int i =0; i< p.gridPuyo.size(); i++){
        	for(int j = 0; j<p.gridPuyo[i].size(); j++){
			switch(p.gridPuyo[i][j]){
				case p.couleursD::VIDE:
					fichierResultat << ".";
					break;
				case p.couleursD::ROUGE:
					fichierResultat << "R";
					break;
				case p.couleursD::VERT:
					fichierResultat << "V";
					break;
				case p.couleursD::JAUNE:
					fichierResultat << "J";
					break;
				case p.couleursD::BLEU:
					fichierResultat << "B";
					break;
				case p.couleursD::MAGENTA:
					fichierResultat << "M";
					break;
				}
		}
			 fichierResultat << endl;
	}

	fichierResultat << score;  //  ecrit le score en fin de fichier 


	fichierResultat.close(); //fermeture du fichier
	return 0;
}
