#ifndef TERRAIN_H_INCLUDED
#define TERRAIN_H_INCLUDED
#include "PuyoP.hpp"
#include <vector>
#include <string>




void clear();
void ini();
void afficherT();
//void setApparition(std::vector<std::vector<int>> p);//va mettre les Puyos au debut pour pouvoir les jouer
bool setApparitionT(std::vector<std::vector<int>> d);
void setApparition(std::vector<std::vector<int>> d);
int getDLA();
int getDLO();
int  getVCouleursD(std::string s);
std::vector<std::vector<int>> getCoup();
void refresh();
void reload();
void Coup(std::vector<std::vector<int>> c);
void setCoup(std::vector<std::vector<int>>);
void setRota(int r);
int getRota();
bool verifVoisinage(int x,int y,char direction);
bool estPresent(std::vector<int> v, size_t i);
bool estPresent(std::vector<std::vector<int>> v,size_t i);
bool estPresent(std::vector<std::vector<int>> v, std::vector<int> v1);
bool testG();
bool gP(int x, int y);
bool gravite();
bool allFalse(std::vector<bool> t);  
bool gCoup();
void cleanC();
bool estEgal(std::vector<int> t,std::vector<int> y);
std::vector<std::vector<int>> supprimerDoublon(std::vector<std::vector<int>> t);
std::vector<std::vector<int>> separer(std::vector<std::vector<int>> selection, int x);
void vider(std::vector<std::vector<int>> selection, std::vector<int> &points);
std::vector<int> detection2(std::vector<int> points);
std::vector<int> detection1(std::vector<int> points);
void selection2(int x, int y, std::vector<std::vector<int>> &selection);
std::vector<std::vector<int>> getGrid();
PuyoP getPuyoP();
 #endif