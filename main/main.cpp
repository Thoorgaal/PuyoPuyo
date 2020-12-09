#include "../GUI/Fenetre.hpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
//#include "../moteurLogique/terrain.h"
#include <string.h>
#include <vector>
//#include "../GUI/Fenetre.hpp" 
//#include "../moteurLogique/fichiersortie.h"
// 0 mode solo, 1 mode IA, 2 mode simulation

using namespace std;


int main(int argc, char* argv[]){
	/*execute le jeu
  confiance = 90% : le main a toujours fonctionnée pour le moment et n'a pas de bog
  par Ines*/ 
 	
	if ( argc == 2) {  // verifie que seulement deux arguments sont donnes ( ex : ./main solo.txt)
		std::cout << " Fichier entrée = "<< argv[1] << std::endl;
	} else {
		std::cout << std::endl << "Vous devez indiquer un fichier d'entré en paramètre "<< std::endl,
		std::cout << std::endl << " Exemple : "<< argv[0] << "solo.txt" << std::endl << std::endl;
		return -1;
	} 
	
	
	Fenetre fen(argv[1]);
	//commencerPartie(argv[1]);
	
	return 0;
}

