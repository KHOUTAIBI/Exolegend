#include "./headers/bomb.h"

int dropbomb(Gladiator * gladiator){
    if(gladiator->weapon->getBombCount() > 0){
        gladiator->weapon->dropBombs(1);
        return 2;
    }
    else{
        return 0;
    }
}