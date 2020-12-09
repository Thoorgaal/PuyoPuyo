#include "terrain.h"
#include "PuyoP.hpp"	
#include <iostream>
#include <vector>
#include <string>
#include "partie.h"

	
#define ASSERT(C) if ( !(C) ) { std::cerr << "Test failed: "#C << std::endl; }
using namespace std;
	
PuyoP p;
vector<vector<int>> coup = vector<vector<int>>(2); //sa taille sera 2 2  et le [i][0] le xi et le [i][1] le yi et le [i][3] sera la 
												   // par defaut ce sera vide

//je fais ca pour eviter d'utiliser system("cls") ou sysstem("clear") ainsi que pour eviter les 
//problemes d'os
void clear(){
	for(int n = 0; n<5; n++){
		cout << "\n\n\n\n\n\n\n" << endl;
	}
}
//Initialise le terrain vide 
void ini(){
	for(int i = 0; i<2; i++){
		coup[i] = vector<int>(4);
		for(int j = 0 ; j<2; j++){
			coup[i][j] = -1;
		}
		coup[i][2] = p.couleursD::VIDE;
		coup[i][3] = 1;
	}
//affiche le terrain dans l'etat dans lequel il est
}
void afficherT(){
	for(int i = 0; i<coup.size();i++){
		coup[i][3] =1;
	}
	clear();
	for(int i =0; i<= p.gridPuyo.size(); i++){ 
		if(i!=p.gridPuyo.size()) cout << "|";
		else cout << " ";
		for(int j = 0; j<p.gridPuyo[i%p.dLo].size();j++){	
			if(i!=p.gridPuyo.size()){
				switch(p.gridPuyo[i][j]){
					case p.couleursD::VIDE:
						cout << " ";
					break;
					case p.couleursD::ROUGE:
						cout << "r";
					break;
					case p.couleursD::VERT:
						cout << "v";
					break;
					case p.couleursD::JAUNE:
						cout << "j";
					break;
					case p.couleursD::BLEU:
						cout << "b";
					break;
					case p.couleursD::MAGENTA:
						cout << "m";
					break;
				}
			 }else cout << "-";
		}
		if(i!=p.gridPuyo.size())cout << "|" << endl;
		else cout << endl;
	}
}
//vérifie que le voisins et vide dans la direction demandée
bool verifVoisinage(int x,int y,char direction){
	if(direction == 'h'){ 
		if( y == 0) return false;
		else return p.gridPuyo[y-1][x] == p.couleursD::VIDE ;
	}else if(direction == 'b'){
		if(y == getDLO()-1) return false;
		else return p.gridPuyo[y+1][x] == p.couleursD::VIDE;
	}else if(direction == 'g'){
		if(x == 0) return false;
		else return p.gridPuyo[y][x-1] == p.couleursD::VIDE;
	}else if(direction == 'd'){
		if(x == getDLA()-1) return false;
		else return (p.gridPuyo[y][x+1] == p.couleursD::VIDE) ;
	}
	return false;
}
//comme son nom l'indique, il met en place les pions ou ils faut qu'ils soient et vérifie si il y a défaite
bool setApparitionT(vector<vector<int>> d){
	for(int i=0; i<d.size(); i++){
		if(p.gridPuyo[0][d[i][1]] == p.couleursD::VIDE){	
			p.gridPuyo[0][d[i][1]] = d[i][0];
			coup[i][0] = d[i][1];
			coup[i][1] = 0; 
			coup[i][2] = d[i][0];
			coup[i][3] = 1;
			p.rota =0;
		}else{
			return true;
		}
	}
	p.rota = 0;
	return false;
}
void setApparition(vector<vector<int>> d){
	for(int i=0; i<d.size(); i++){
			p.gridPuyo[0][d[i][1]] = d[i][0];
			coup[i][0] = d[i][1];
			coup[i][1] = 0; 
			coup[i][2] = d[i][0];
			coup[i][3] = 1;
	}
	p.rota = 0;
}


int getDLA(){
	return p.dLa;
}

int getDLO(){
	return p.dLo;
}	

//cette classe prendra en paramaetre un string et rendra le chiffre associe a sa valeur dans l'enumeration
int  getVCouleursD(string s){ 
	ASSERT( s == "couleursD::VIDE"||s == "couleursD::ROUGE"|| s == "couleursD::VERT"||s == "couleursD::JAUNE"||s == "couleursD::BLEU"||s == "couleursD::MAGENTA" );
	if(s == "couleursD::VIDE") return p.couleursD::VIDE;
	else if(s == "couleursD::ROUGE") return p.couleursD::ROUGE;
	else if(s == "couleursD::VERT") return p.couleursD::VERT;
	else if(s == "couleursD::JAUNE") return p.couleursD::JAUNE;
	else if(s == "couleursD::BLEU") return p.couleursD::BLEU;
	else if(s == "couleursD::MAGENTA") return p.couleursD::MAGENTA;
	
	return -1;
}
vector<vector<int>> getCoup(){
	return coup;
}
//fait une sorte de reload de l'etat du terrain en fonction du coup
void refresh(){
	for(size_t i = 0; i<coup.size(); i++){
		 p.gridPuyo[coup[i][1]][coup[i][0]] = p.couleursD::VIDE;	
		
	}
	
}
//cette fonction fait apparaitre le coup dans la grille de Puyos
void reload(){
	for(size_t i = 0; i<coup.size(); i++){
		p.gridPuyo[coup[i][1]][coup[i][0]] = coup[i][2];
	}
}
void Coup(vector<vector<int>> c){
	for(size_t i = 0; i<c.size(); i++){
		for(size_t j =0; j < c[i].size();j++){
			cout << c[i][j] << " c " << i << " i " << coup[i][j] << " coup " << j  << "j"<< endl;
		}
	}
	coup = c;
}
void setRota(int r){
	p.rota = r;
}
int getRota(){
	return p.rota;
}
bool estPresent(vector<int>v, size_t i){
	for(int a:v){
		if(a=i){
			return true;
		}
	}
	return false;
}
bool estPresent(vector<vector<int>> v, size_t i){
	for(vector<int> a:v){
		if(estPresent(a,i)){
			return true;
		}
	}
	return false;
}
bool estPresent(vector<vector<int>> v, vector<int> v1){
	for(size_t i = 0; i<v.size(); i++){
		bool test = true;
		for(int j = 0; j<v[i].size(); j++){
			if(v1[j] != v[i][j]) test = false;
			
		}
		if(test) return true;
	}
	return false;
}
bool tesG(){
	for(size_t i =0; i<p.gridPuyo.size();i++){
		for(size_t j =0; j<p.gridPuyo[i].size(); j++){
			if(p.gridPuyo[i][j] != p.couleursD::VIDE && verifVoisinage(j,i,'b')) return false;
		}
	}
	return true;
}
//cette fonction vérifie la gravité pour une pièce, elle est utilisée dans gravite et la gravite des coups
bool gP(int x, int y){
		if(verifVoisinage(x,y,'b')){
			p.gridPuyo[y+1][x] = p.gridPuyo[y][x];
			p.gridPuyo[y][x] = p.couleursD::VIDE;
			return true;
		}
	
	return false;
}
bool  gravite(){ //cette fonction regarde quels elements doivent subir la gravite et leur font subir
	bool g = false;
		for(size_t i = p.gridPuyo.size()-1; (i+1)>=1; i--){
			for(int j = 0; j<p.gridPuyo[i].size(); j++){
				if(p.gridPuyo[i][j]!=p.couleursD::VIDE){
					bool test = gP(j,i);
					if(test) g = true;
				}
			}
		}
	

	
	return g;
}



bool allFalse(vector<bool> t){
	for(size_t i=0; i<t.size();i++){
		if(t[i]){
			return false;
		}
	}
	return true;
} 
//applique la gravité au coup en fonction de sa rotation
bool gCoup(){
	
	reload();
	bool test = true;
	if(p.rota == 1){
		if(!verifVoisinage(coup[coup.size()-1][0],coup[coup.size()-1][1],'b')) test=false;
		for(size_t i = coup.size()-1; i+1>=1; i--){
			if(gP(coup[i][0], coup[i][1])){
				coup[i][1]++;
							
			}
		}
			
	}else if(p.rota == 3){
		if(!verifVoisinage(coup[0][0],coup[0][1],'b')) test=false;
		for(size_t i = 0; i<coup.size(); i++){
			if(gP(coup[i][0], coup[i][1])){
				coup[i][1]++;
			}
		}
	}else{	
		for(size_t i = 0; i<coup.size(); i++){
			if(gP(coup[i][0], coup[i][1])){
				coup[i][1]++;
			}else{
				test = false;
			}
		}
	}
	return test;
}


bool estEgal(vector<int> t, vector<int>y){
	if(t.size() == y.size()){
		bool a = true;
		for(size_t i = 0;i<t.size(); i++){
			if(t[i]!=y[i])a = false;
		}
		return a;
	}else{
		return false;
	}
}
//fait par jolan confiance tres grande 
vector<vector<int>> supprimerDoublon(vector<vector<int>> t){
	vector<vector<int>> comparaison = vector<vector<int>>(0);
	while(t.size()>0){
		comparaison.resize(comparaison.size()+1);
		comparaison[comparaison.size()-1] = t[0];
		vector<size_t> indice= vector<size_t>(0);
		for(size_t j = 0; j<t.size(); j++){
			bool comp = estEgal(t[0],t[j]);
			
			if(comp){
				indice.resize(indice.size()+1);
				indice[indice.size()-1] = j;
			}
		}
		size_t i = t.size();
		for(size_t j=0;j<indice.size(); j++){
			t.erase(t.begin()+indice[j]-(i-t.size()));
		}
		
		
	}
	return comparaison;	
	
}
//cette fontion prend un tableau et le séparer dès qu'il atteint le séparateur -1
//cette fontion prend un tableau et le séparer dès qu'il atteint le séparateur -1
vector<vector<int>> separer(vector<vector<int>> selection, int x){
	vector<vector<int>> sSepare = vector<vector<int>>(0);
	for(int i = x; i<selection.size(); i++){
		if(selection[i].size() > 1){
			sSepare.resize(sSepare.size()+1);
			if(sSepare.size()>0){
				sSepare[sSepare.size()-1] = vector<int>(2);
			}else{
			 	sSepare[0] = vector<int>(2);
			}
			for(size_t j=0;j<2;j++){
				sSepare[sSepare.size()-1][j] = selection[i][j];
			}}else{
		return sSepare;
		}
	}
	return sSepare;
}

//vide les pieces selectionnees si elles sont au minimum quatre

void vider(vector<vector<int>> selection,vector<int> &points){
	int ax = 0;
	vector<vector<int>>sSepare= vector<vector<int>>(0);
	while(ax<selection.size()){
		sSepare = separer(selection,ax);
		ax+=sSepare.size()+1;
		sSepare = supprimerDoublon(sSepare);
		if(sSepare.size()>=4){
			for(size_t i = 0; i<sSepare.size(); i++){
				p.gridPuyo[sSepare[i][1]][sSepare[i][0]] = p.couleursD::VIDE;
				points[0]++;
			}
			points[1]++;
		}
	}

}
//cette fonction testera toute la grille selon le test 2 (entre chaque groupe selectionné
// il y aura un séparateur {-1} qui servira  a la detection et le vidage des
// sélections)
// vérifie des 4 cotés à chaque fois que il n'y a pas de mêmes couleurs : si elle trouve un même puyo, elle va vers lui mais une fois que le 
vector<int> detection2(vector<int> points){
	vector<vector<int>> selection = vector<vector<int>>(0);
	for(int  i=0; i<p.gridPuyo.size(); i++){
		
		for(int j=0;j<p.gridPuyo[i].size(); j++){
			if(p.gridPuyo[i][j]!=p.couleursD::VIDE){
				
					if(j!=getDLA()-1){
						if(p.gridPuyo[i][j+1] == p.gridPuyo[i][j]){
							if(!estPresent(selection, {j+1,i})|| selection.size() == 0){
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i;
								selection[selection.size()-1][0] = j+1;
								selection2((j+1) ,i,selection);
								
							}
						}
					}if(i!=getDLO()-1){
						if(p.gridPuyo[i+1][j]==p.gridPuyo[i][j]){
							if(!estPresent(selection, {j,i+1})|| selection.size() == 0){ 
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i+1;
								selection[selection.size()-1][0] = j;
								selection2(j,(i+1),selection);
							}
						}
					}if( j!=0){
						if(p.gridPuyo[i][j-1]==p.gridPuyo[i][j]){
							if(!estPresent(selection, {j-1,i})|| selection.size() == 0){ 	
								selection.resize(selection.size()+1);	
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i;
								selection[selection.size()-1][0] = j-1;
								selection2((j-1),i,selection);
								
							}
						 }
					}if(i!=0){
						if(p.gridPuyo[i-1][j]==p.gridPuyo[i][j]){
							if(!estPresent(selection, {j,i-1})|| selection.size() == 0){ 
								selection.resize(selection.size()+1);	
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i;
								selection[selection.size()-1][0] = j-1;
								selection2(j,(i-1),selection);
							}
						}
					}
					
					selection.resize(selection.size()+1);
					selection[selection.size()-1] = {-1};
				}	
			}

			
			

		}
		vider(selection, points);
		return points;
}
vector<int> detection1(vector<int> points){
	vector<vector<int>>selection =vector<vector<int>>(0);
	for(size_t i = 0; i<p.gridPuyo.size(); i++){
		for(size_t j=0; j<p.gridPuyo.size(); i++){
			if(p.gridPuyo[i][j]!=p.couleursD::VIDE ){
				selection.resize(selection.size()+1);
				selection[selection.size()-1] = vector<int>(2);
				selection[selection.size()-1][1] = i;
				selection[selection.size()-1][0] = j;
				if(j != getDLA()){
					if(p.gridPuyo[i][j+1] == p.gridPuyo[i][j]){

						int  jj =j+1;
						if(jj!=p.dLo){
							while(p.gridPuyo[i][jj+1] == p.gridPuyo[i][j]){
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i;
								selection[selection.size()-1][0] = jj+1;
								jj++;
								if(jj==p.dLo) break;
							}
						}
					}
				}else if(i != getDLO()){
					 if(p.gridPuyo[i+1][j] == p.gridPuyo[i][j]){
					
						int  ii =i+1;
						if(ii!=p.dLo){
							while(p.gridPuyo[ii+1][j] == p.gridPuyo[i][j]){
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = ii+1;
								selection[selection.size()-1][0] = j;
								ii++;
								if(ii==p.dLo) break;
							}
						}
					}
				}else if(i !=0){
					 if(p.gridPuyo[i-1][j] == p.gridPuyo[i][j]){
					
						int  ii =i-1;
						if(ii!=0){
							while(p.gridPuyo[ii-1][j] == p.gridPuyo[i][j]){
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = ii-1;
								selection[selection.size()-1][0] = j;
								ii--;
								if(ii==p.dLo) break;
							}
						}
					
				}else if(j !=0){
					 if(p.gridPuyo[i][j-1] == p.gridPuyo[i][j]){
					
						int  jj =j-1;
						if(jj!=0){
							while(p.gridPuyo[i][jj-1] == p.gridPuyo[i][j]){
								selection.resize(selection.size()+1);
								selection[selection.size()-1] = vector<int>(2);
								selection[selection.size()-1][1] = i;
								selection[selection.size()-1][0] = jj-1;
								jj--;
								if(jj==p.dLo) break;
							}
						}
					
				}

			}
			selection.resize(selection.size()+1);
			selection[selection.size()-1] = vector<int>(1);
			selection[i][0]=-1;
		}
	}}}
	vider(selection, points);
	return points;
}
//pareil que la selection 1 mais jusqu'a que ce ne soit plus la meme valeur
void selection2(int x, int y, vector<vector<int>> &selection){
	int co = p.gridPuyo[y][x];
	
	if(y!=getDLO()-1){
		if(co == p.gridPuyo[y+1][x]){
			if(!estPresent(selection,{x,y+1})){
				selection.resize(selection.size()+1);
				selection[selection.size()-1] = vector<int>(2);
				selection[selection.size()-1][0] = x;
				selection[selection.size()-1][1] = y+1;
				selection2(x,(y+1),selection);
			}
		}
	}if(x!= getDLA()-1){
		if( co==p.gridPuyo[y][x+1] ){
			if(!estPresent(selection,{x+1,y+1})){
				selection.resize(selection.size()+1);
				selection[selection.size()-1] = vector<int>(2);
				selection[selection.size()-1][0] = x+1;
				selection[selection.size()-1][1] = y;
				selection2((x+1),y,selection);
			}
		}
	}if(y!=0){
		if(co==p.gridPuyo[y-1][x]){
			if(!estPresent(selection,{x,y-1})){
				selection.resize(selection.size()+1);
				selection[selection.size()-1] = vector<int>(2);
				selection[selection.size()-1][0] = x;
				selection[selection.size()-1][1] = y-1 ;
				selection2(x,(y-1),selection);
			}
		}		
	}if(x!=0){
		if(co==p.gridPuyo[y][x-1]){
			if(!estPresent(selection,{x-1,y})){
				selection.resize(selection.size()+1);
				selection[selection.size()-1] = vector<int>(2);
				selection[selection.size()-1][0] = x-1;
				selection[selection.size()-1][1] = y;
				selection2((x-1),y,selection);
			}
		}
	}
}
vector<vector<int>> getGrid(){
	return p.gridPuyo;
}
PuyoP getPuyoP(){
	return p;
}