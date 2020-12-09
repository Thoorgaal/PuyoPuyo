#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// le but de ce programme est d ecrire des fichiers d entree aleatoire selon les trois modes : IA / SOLO / SIMULATION

int aleaint(int a, int b) {           // fonction qui renvoie un nombre aleatoire entre les deux donnes
        return (rand() % (b - a) + a);
    }

int creerFichier() {         
    /** cette fonction cree des fichiers d entree selon et les ecrit selon le mode dans trois fichiers texte
    cette fonction a ete testee plusieurs fois et ecrit a chaque fois des nouveaux fichiers d entree 
    sous le format attendu - confiance = 100%
    par Ines **/
    ofstream fichierSimulation, fichierSolo, fichierIA;  // declaration du fichier
    fichierSimulation.open("entreeSimulation.txt", ios::out);  //ouverture du fichier pour le mode simulation
    fichierSolo.open("entreeSolo.txt", ios::out);  // ouverture du fichier pour le mode solo
    fichierIA.open("entreeIA.txt", ios::out);   // ouverture du fichier pour le mode IA
    if ( fichierIA.bad() || fichierSimulation.bad() || fichierSolo.bad()) {   // teste si l'un des fichiers s'ouvre mal
        return -1;
    }
    int colonne;
    int rotation;
    char piece[2];
    char TabPuyo [] = {'B','J','M','R','V'};  
    int NombreTours = aleaint ( 50,200);   // le nombre de tours de jeu sera entre 50 et 200
    fichierSimulation << "MODE SIMULATION"<< endl;  // ecrit en haut du fichier simulation
    fichierIA << "MODE IA" <<endl;   // ecrit en haut du fichier IA
    fichierSolo<< "MODE SOLO"<<endl;  // ecrit en haut du fichier solo
    while ( NombreTours--) {     // tant que le nombre de tour n'est pas atteint, la boucle recommence
        piece[0] = TabPuyo[aleaint(0,4)];    // la 1e piece prend une valeur aleatoire de TabPuyo
        piece[1] = TabPuyo[aleaint(0,4)];    // pareil pour la 2e piece
        rotation = aleaint (0,3);  
        colonne = aleaint (0,5); 
        fichierSimulation << piece[0]<< piece[1]<<endl<< rotation<< " "<< colonne<<endl; // ecrit dans le fichier simulation les deux pieces puis la rotation et la colonne
        fichierIA << rotation << " "<< colonne<< endl; // ecrit dans le fichier IA la rotation puis la colonne
        fichierSolo << piece[0]<<piece[1]<< endl;   // ecrit dans le fichier solo les deux pieces tirees
    }
    fichierIA.close(); // ferme les fichiers tour a tour
    fichierSolo.close();
    fichierSimulation.close();
    return 0;
}

int main() {
    creerFichier();
}