#include "terrain.h"
#define ASSERT(C) if ( !(C) ) { std::cerr << "Test failed: "#C << std::endl; }

void test(){
    ASSERT(getVCouleursD("couleursD::MAGENTA" == 5));
    ASSERT(getVCouleursD("couleursD::ROUGE" == 1));
}