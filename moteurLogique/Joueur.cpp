#include "Joueur.h"
#include "terrain.h"
#include <iostream>
#include <string>

//auteur Jolan, confiance: haute
using namespace std;
//cette fonction fera en sorte de lire l'entrée utilisateur et fera l'action qui lui est lié
void Joueur::appliquerRota(int r,int r2){
    
    
        //la je fais les rotations et je regarde si c'est possible de les appliquer et si oui je les applique
        vector<vector<int>> c = getCoup();
        
        
        if(r!=r2){
            if(r == 0 && r2 == 1 && verifVoisinage(c[0][0],c[0][1],'b')){
                c[1][0]--;
                c[1][1]++; 
                setRota(r2);    
            }else if(r == 1 && r2 == 2 && verifVoisinage(c[0][0],c[0][1],'d')){
               c[1][1]--;
                c[0][0]++;
                setRota(r2);
            }else if(r == 2 && r2 == 3 && verifVoisinage(c[0][0],c[0][1],'d')){
                c[0][0]--;
                c[0][1]++;
                setRota(r2);
            }else if(r == 3 && r2 == 0 && verifVoisinage(c[1][0],c[1][1],'d')){
                c[0][1]--;
                c[1][0]++;
                setRota(r2);
            }else if(r == 1 && r2 == 0 && verifVoisinage(c[0][0],c[0][1],'d')){
                c[1][1]--;
                c[1][0]++;
                setRota(r2);
            }else if(r == 2 && r2 == 1 && verifVoisinage(c[1][0],c[1][1],'b')){
                c[1][1]++;
                c[0][0]-=1;
                setRota(r2);
            }else if(r == 3 && r2 == 2 && verifVoisinage(c[1][0],c[1][1],'d')){
                c[0][0]++;
                c[0][1]--;
                setRota(r2);
            }else if(r == 0 && r2 == 3 && verifVoisinage(c[0][0],c[0][1],'d')){
               c[1][0]-=1;
               c[0][1]+=1;
               setRota(r2);
            }
            
        }
        for(size_t i=0; i<c.size(); i++){
            for(size_t j =0; j<2; j++){
                cout << c[i][j] << " je test " << c[i].size() << " " << c.size() << endl;
            }
        } 
        
        Coup(c);
}
void Joueur::appliquerDirection(bool direction){
    vector<vector<int>> c = getCoup();
    if(direction){
        if(verifVoisinage(c[0][0],c[0][1],'d') && verifVoisinage(c[1][0],c[1][1],'d') ){
                for(int i = 0; i<c.size(); i++){
                    c[i][0] ++;    
                }
            }
    }else{
        if(verifVoisinage(c[0][0],c[0][1],'g') && verifVoisinage(c[1][0],c[1][1],'g') )
            for(int i = 0; i<c.size(); i++){
                if(c[i][3]!=0)c[i][0] -=1;
        }    
    }
    Coup(c);
}



bool Joueur::verifCO(){
    for(size_t i = 0; i<getCoup().size(); i++){
        if(getCoup()[i][3] == 0){
            return true;
        }
    }
    return false;
}
bool Joueur::verifCP(){
    for(size_t i = 0; i<getCoup().size(); i++){
        if(getCoup()[i][1] == getDLO()-1 || this->verifCO()) return false;
    }
    return true;
}



//demande au joueur ce qu'il veut jouer et applique la modification
 void Joueur::agirT(){
     if(this->verifCP()){
        refresh();
        vector<vector<int>> c = getCoup();
        char act;
        int r = getRota();
        cin >> act;
        int dLa = getDLA();
        switch(act){
            case 'z':
                if(r!=3){ 
                    appliquerRota(r, r+1);
                }else{
                    appliquerRota(r,0);
                }
                break;
            case 's':
                if(r!=0){ 
                    appliquerRota(r,r-1); 

                }else{
                    appliquerRota(r,3);
                }
                break;
            case 'd':
                appliquerDirection(true);
                break;
            case 'q':
                appliquerDirection(false);
            }
        //la je fais les rotations et je regarde si c'est possible de les appliquer et si oui je les applique
            
        
        
     }
 }



  bool Joueur::agir(){
     
        refresh();
        cout << "bonjour" << endl;
        vector<vector<int>> c = getCoup();
        char act;
        int r = getRota();
        cout << " Entrez votre choix ( d=droite, q=gauche, z=+1 sur la rotation , s=-1 sur la rotation  e pour confirmer la collonne)  votre score est de : " << score <<"." << endl;
        cin >> act;
        int dLa = getDLA();
        switch(act){
            case 'z':
                if(r!=3){ 
                    setRota(r+1);
                }else{
                    setRota(0);
                }
                break;
            case 's':
                if(r!=0){ 
                    setRota(r-1); 

                }else{
                    setRota(3);
                }
                break;
            case 'e':
                return false;
                break;
            case 'd':
                appliquerDirection(true);
                break;
            case 'q':
                if(verifVoisinage(c[0][0],c[0][1],'g') && verifVoisinage(c[1][0],c[1][1],'g') )
                    for(int i = 0; i<c.size(); i++){
                    if(c[i][3]!=0)c[i][0] -=1;
                    }
            }
        
        Coup(c);
        return true;
        
     
 }



 void Joueur::zSolo(){
     refresh();
         int r = getRota();
         
         
        if(r<3)appliquerRota(r,r+1);
        else appliquerRota(r,0);
 }
 void Joueur::sSolo(){
    refresh();
    int r = getRota();
    
    if(r>0) appliquerRota(r,r-1);
    else appliquerRota(r, 3);
}
void Joueur::qSolo(){
    refresh();
    appliquerDirection(false);
}
void Joueur::dSolo(){
    refresh();
    appliquerDirection(true);
}