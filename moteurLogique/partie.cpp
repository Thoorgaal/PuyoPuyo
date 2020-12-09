#include "partie.h"
#include "rand.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Joueur.h"
#include <math.h>
#include "fichiersortie.h"
#include <string.h>
#include <chrono>
#include <thread>
#include "fichiersortie.h"
// ce programme a pour but d'executer les differentes parties selon leur mode 
#include "../GUI/Fenetre.hpp"
#include "Joueur.h"



using namespace std;

char fileIN[256];
int score = 0;

vector<int> points = vector<int>(3);//le 0 sera les puyos, le 1 les groupes, le 2 les combos
bool Defaite = false;
//toutes les fonctions pour le comptage de points: auteur: Jolan, confiance: eleve
void  cleanP(){
    for(size_t i =0; i<3; i++){
//        cout << points[i] << " point(s) "<< endl;
        points[i] = 0;

    }
}
void compterScore(Joueur &j){
    j.score+=(long) 10*points[0]*(pow(4,points[2])+ pow(3,points[1])) ;
  if(j.score>999999)j.score = 999999;
    score = j.score;
    cout <<"Vous avez gagne " << j.score << " points" << endl;
    cleanP(); 
    grilleFinale(j.score);

}
void setDimT(vector<vector<int>> &p){
    p[0][1] = aleaint(0,getDLA()-1);
    p[1][1] = p[0][1] +1;
    p[1][0] = aleaint(1,getVCouleursD("couleursD::MAGENTA"));
    p[0][0] = aleaint(251,251 +getVCouleursD("couleursD::MAGENTA"))-250  ;//si je ne fais pas ca je ne sais pas ca, je ne sais pas
    //pourquoi mais ca ne s'instentie pas bien 
}


bool setCoupT(){
    vector<vector<int>> dim = vector<vector<int>>(2); 
    for(int i  = 0; i<dim.size(); i++){
        dim[i] = vector<int>(2); // le 0 sera la couleur et le 1 la pos x
    } 
    setDimT(dim);
    
    return setApparitionT(dim);
}

void setDim(vector<vector<int>> &p){
    p[0][1] = aleaint(0,getDLA()-1);
    p[1][1] = p[0][1] +1;
    p[1][0] = aleaint(1,getVCouleursD("couleursD::MAGENTA"));
    p[0][0] = aleaint(251,251 +getVCouleursD("couleursD::MAGENTA"))-250  ;//si je ne fais pas ca je ne sais pas ca, je ne sais pas
    //pourquoi mais ca ne s'instentie pas bien 
}

int getShortVcouleursD (char color) {
    switch(color) {
    case 'M':
        return getVCouleursD("couleursD::MAGENTA");
    case 'R':
        return getVCouleursD("couleursD::ROUGE");
    case 'J':
        return getVCouleursD("couleursD::JAUNE");
    case 'B':
        return getVCouleursD("couleursD::BLEU");
    case 'V':
        return getVCouleursD("couleursD::VERT");
    default:
        return -1;
    }
}

void setGivenDim(vector<vector<int>> &p, char puyo1, char puyo2, int rotation, int colonne) {
/** Place le coup selon les parametres donnes
 * @ param tableau 
 * @ param puyo 1, puyo 2, les differentes couleurs de puyos donnes/tires
 * @ param rotation la rotation donnee/tiree
 * @ param colonne la colonne choisie/donnee
 * confiance = 100% : pas de bog et les tests ont toujours fonctionnes
 * par Ines
 * **/
    p[0][0]= getShortVcouleursD(puyo1);
    p[0][1]= colonne;
    p[1][0]= getShortVcouleursD(puyo2);
    if ( rotation == 0) {
        p[1][1] = colonne+1;
    } else {
        p[1][1] = colonne;
    }
}


void setCoup(){
//  cette fonction place le coup
    vector<vector<int>> dim = vector<vector<int>>(2); 
    for(int i  = 0; i<dim.size(); i++){
        dim[i] = vector<int>(2); // le 0 sera la couleur et le 1 la pos x
    } 
    setDim(dim);
    
    setApparition(dim);
}

void setCoupWithPieceAndRotationAndColonne ( char puyo1, char puyo2, int rotation, int colonne) {
    /** définit le coup en fonction des nouvelles pièces, rotation et colonne 
    * @ param puyo1 et puyo2 les couleurs des deux puyos tires/choisis
    * @ param rotation la rotation choisie/donnee
    * @ param colonne la colonne choisie/tiree
    * pour le mode simulation ( car toutes les données sont présentes)
    * confiance = 100% : a toujours fonctionne et passe les tests
    * par Ines **/
    vector<vector<int>> dim = vector<vector<int>>(2);
    for ( int i = 0; i<dim.size();i++) {
        dim[i] = vector<int>(2); // le 0 sera la souleur et le 1 la position 
    }
    setGivenDim(dim,puyo1,puyo2,rotation,colonne);
    setApparition(dim);
}

void setCoupWithPiece(char puyo1, char puyo2) {
    /** définit  mode = m;le coup selon les nouvelles pièces
    * pour le mode solo ( car que les couleurs sont présentes, mais demandera au joueur la rotation et colonne choisie)
    * @ param puyo1 et puyo 2 les couleurs des deux puyos donnes
    * confiance = 100% : pas de bog et passe les tests
    * par Inès **/
    vector<vector<int>>dim = vector<vector<int>>(2);
    int rotation = 0;
    int colonne =3;
    for ( int i =0; i<dim.size();i++) {
        dim[i] = vector<int>(2); // 0 sera la couleur et 1 la position
    }
    setGivenDim( dim, puyo1,puyo2,rotation,colonne);
    setApparition(dim);
}

bool goodFileIN ( ifstream & ifsIN, string & fileheader) {
/** verifie que le fichier donne est valable : dans le bon format et s ouvre bien
 * @ param ifsIN l'identifiant du fichier
 * @ param fileheader la premiere ligne du fichier
 * confiance = 100% : passe les tests et a toujours fonctionne 
 * par Ines **/
    string firstLine;
    if (!ifsIN.is_open()) {
        cout << "Impossible d'ouvrir le fichier en lecture !"<< endl;
        return false;
    } 
    if (getline (ifsIN, firstLine)){
	if (firstLine != fileheader) {
		cout << "L'entete du fichier ne correspond pas au mode du jeu!"<<endl;
		return false;
	}
    } else {
	cout << "L'entete du fichier ne correspond pas au mode du jeu!"<<endl;
	return false;
    }
    return true;
}

void solo(Fenetre* fen) {
/** cette fonction contient le deroulement de la partie en mode solo
 * de plus, elle ecrira le deroulement de la partie sous la forme du mode simulation pour la rejouer facilement
 * confiance = 95% : a toujours fonctionne et n'a pas de bog
 * par Ines **/
    bool started = false;
    Joueur j1;
    
    int c = 0;
    bool finPartie = false;
    string piece="BR";
    char puyo1, puyo2;
    int rotation=0;
    int colonne=3;
    string fileHeader="MODE SOLO";
    ifstream ifsIN;  // declare le fichier d entree
    ofstream simuFile;
    string simuFileName="simulationfromsolo.txt";  
    ifsIN.open(fileIN);  // ouvre le fichier FILEIN
    if ( !goodFileIN ( ifsIN, fileHeader)) { 
	    return;
    }
    simuFile.open(simuFileName);  // ouvre le fichier simuFileName
    if (!simuFile.is_open()) { // teste si le fichier s est bien ouvert
        cout << "Impossible d'ouvrir le fichier en lecture !"<< endl;
        return ;
    } 

    simuFile << "MODE SIMULATION" << endl;  // ecrit en haut du fichier

    while(!finPartie){
        bool tour = true;
        cout << "nouveau tour" << endl;
        piece="";
        ifsIN >> piece;
        if (piece[0] == '\0'){
        cout << "Fin de fichier atteinte " << endl;
        return;
        }
        puyo1=piece[0];
        puyo2=piece[1];
        setCoupWithPiece(puyo1, puyo2 );
            bool tJoueur = true;
            while(tJoueur){
//              //fen->afficherGT(j1.score);  
                fen->afficherGT(j1.score);  
                cout << j1.score << " score"<< endl; 
                std::cout << "ah" << std::endl;     
                tJoueur = fen->action(j1);
                cout << "entrer" << endl;
                //tJoueur = false;
                reload();
            }
            rotation = getRota();
            colonne = getCoup()[0][0];
            simuFile << puyo1 << puyo2 << endl;  // ecrit les deux couleurs de puyos dans le fichier a chaque tour
            simuFile << rotation << " "<<colonne << endl;  // ecrit la rotation et la colonne a chaque tour : comme dans le mode simulation
            bool g = true;
            while(g) g=gravite();
            for(size_t i =0; i<getDLA(); i++){
                if(getGrid()[0][i]!=0){
//                    afficherT();();
                    fen->afficherGT(j1.score); 
                    cout << "salut " << getGrid()[0][i];
                    finPartie = true;
                    break;
                }
            }
            if(!finPartie){
                bool selection = true;
                do{
                    selection = false;
                    int aP = points[0];
                    points = detection2(points);
                    g=true;
                    while(g)g = gravite();
                    if(points[0]>aP){
                        points[2]++;
                        selection =true;
                    }
                    fen->afficherGT(j1.score);//fen->afficherGT(j1.score);
                }while(selection);
                compterScore(j1);
            }
    }
}

char getPieceAlea() {
/** cette fonction genere des pieces aleatoires
 * confiance = 100% : pas de bog et fonctionne toujours
 * par Ines**/
    int color = aleaint(0,4);
    char tab[]= {'B','J','M','R','V'};
    return tab[color];
}
/** ZONE DE TEST 
 * ASSERT ( getPieceAlea() == ('B' or 'J' or 'M' or 'R' or 'V'));
 * **/

void IA(Fenetre* fen){
    bool started = false;
    /** contient le déroulement de la partie en mode IA
     * confiance = 95% : a toujours marche et n'a pas de bog
     * par Ines **/
    Joueur j1;
    int c = 0;
    int rotation;
    int colonne;
    bool defaite = false;
    string piece="BR";
    char puyo1, puyo2;
    string fileHeader="MODE IA";
    ifstream ifsIN;
    ifsIN.open(fileIN);
    if ( !goodFileIN ( ifsIN, fileHeader)) {  // verifie que le fichier donne est compatible avec le mode IA
	    return;
    }

    while(!defaite){  // tant qu'il n'y a pas de defaite la boucle recommence
        bool tour = true;
	    cout << "nouveau tour" << endl;
	    piece="";
	    ifsIN >> piece;  // ecrit les valeurs de piece dans le fichier 
	    if (piece[0] == '\0'){   // quand il n'y a plus de piece dans le fichier on le signale et la partie s'arrete
	        cout << "Fin de fichier atteinte " << endl;
	        return;
	    }
        puyo1=piece[0];
        puyo2=piece[1];
	    rotation=aleaint(0,3);
	    colonne=aleaint(0,5);
        setCoupWithPieceAndRotationAndColonne(puyo1, puyo2,rotation,colonne );
        bool tJoueur = true;
        while(tJoueur){
            fen->afficherGT(j1.score);        
//          j1.agir();
            tJoueur = gCoup();                    
        }
        bool selection = true;
        while(selection){
            points =  detection2(points);
            selection = gravite();
            fen->afficherGT(j1.score);
            if(selection)points[2]++;
        }
        compterScore(j1);
    }
}

void simulation(Fenetre* fen){
    bool started = false;
    /**contient le déroulement de la partie en mode simulation
    * confiance = 95% : n'a pas de bog et a toujours fonctionne 
    * par Inès **/
    Joueur j1;
    int c = 0;
    bool defaite = false;
    string piece="BR";
    char puyo1, puyo2;
    int rotation=0;
    int colonne=3;
    string fileHeader="MODE SIMULATION";
    ifstream ifsIN;
    ifsIN.open(fileIN);   // ouvre le fichier
    if ( !goodFileIN ( ifsIN, fileHeader)) {  // verifie que le fichier est bien ouvert
	return;
    }

    while(!defaite){   // tant que il n'y a pas de defaite, la boucle recommence
        bool tour = true;
	    cout << "nouveau tour" << endl;
	    piece="";
	    ifsIN >> piece;  // ecrit les valeurs de piece dans le fichier
	    if (piece[0] == '\0'){
	        cout << "Fin de fichier atteinte " << endl;
	        return;
	    }
        puyo1=piece[0];
        puyo2=piece[1];
	    ifsIN >> rotation >> colonne;
        setCoupWithPieceAndRotationAndColonne(puyo1, puyo2, rotation, colonne );
        bool tJoueur = true;
        
            while(tJoueur){
                fen->afficherGT(j1.score);        
//                j1.agir();
                tJoueur = gCoup();             


            }
            if(!defaite){
                bool selection = true;
                do{
                    int aP = points[0];
                    points = detection2(points);
                    selection = gravite();
                    if(points[0]>aP){
                        points[2]++;
                    }
                    fen->afficherGT(j1.score);
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }while(selection);
                compterScore(j1);
            }
    }
}

void soloT(Fenetre* fen){
     
    bool sarted = false;
    Joueur j1;
    int c = 0;
    bool defaite = false;
    while(!defaite){
        bool tour = true;
        defaite = setCoupT();
        if(defaite) break;
        bool tJoueur = true;
        while(tJoueur){
           
           //j1.agir();
            tJoueur = gravite();
            fen->afficherGT(j1.score);
                
           }
            gravite();
        bool graviteD = true;
        if(!defaite){
                bool selection = true;
                do{
                    int aP = points[0];
                    points = detection2(points);
                    selection = gravite();
                    if(points[0]>aP){
                        points[2]++;
                    }
                fen->afficherGT(j1.score);
                }while(selection);
                compterScore(j1);
            }
    }
}


//void commencerPartie(int m, Fenetre* fen){
void commencerPartie(char *inputFile,Fenetre* fen){
/** la fonction prend un fichier d entree et verifie si il est dans le bon format
 * si oui, elle lui associe le mode contenu et commence la partie selon celui ci
 * @ param inputFILE un fichier 
 * confiance = 100% : a toujours fonctionné et passé les tests
 * par Ines e**/
    
    int m;
    
    string firstLine;
    ifstream ifsIN;
    ini();
	strcpy(fileIN, inputFile);
    ifsIN.open(inputFile);
    if (!ifsIN.is_open()) {   // teste si le fichier s est bien ouvert
        cout << "Impossible d'ouvrir le fichier en lecture !"<< endl;
        return ;
    } 
    if (getline (ifsIN, firstLine)){   // regarde les donnees de la premiere ligne, contenant normalement le mode et lui attribue sa partie
	    if (firstLine == "MODE SOLO") {
            m=modeP::SOLO;
            fen->mode = modeP::SOLO;
        } else {
	        if (firstLine == "MODE IA") {
                m=modeP::INTA;
                fen->mode = modeP::INTA;
            } else {
	            if (firstLine == "MODE SIMULATION") {
                    m=modeP::SIMULATION;
                    fen->mode = modeP::SIMULATION;
                } else {  // si aucun des modes n est reconnu la fonction le signale
		            cout << "L'entete du fichier ne correspond pas au mode du jeu!"<<endl;
		            return;
                }
            }
        }
    } else {
	    cout << "Vérifiez que le fichier est correct !"<<endl;
	    return;
    }
    ifsIN.close();  // ferme le fichier ifsIN

    switch(m){
        case modeP::SOLO:
            solo(fen); 
        break;
        case modeP::INTA:
            IA(fen);
        break;
        case modeP::SIMULATION:
            simulation(fen);
        break;
        case modeP::SOLOT:
            soloT(fen);
            break;
    }
    Defaite = true;
}
bool getD(){
    return Defaite;
}

char* getFileIN(){
    return fileIN;
}
int getScore(){
    return score;
}