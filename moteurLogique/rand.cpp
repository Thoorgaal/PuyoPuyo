#include "rand.h"
#include <stdlib.h>
#include <time.h>
#include <iostream> 
//prend un minimum, un maximum et donne un nomre aléatoire entre les deux
int aleaint(int a, int b){
    
    
    return (rand() % (b - a) + a);
}