#include "../include/dimension.h"

static DimensionsType currentDimension = INIT_DIMENSION;


void initDimension(void){
    currentDimension = INIT_DIMENSION;
}

void changeDimension(void){
    if(currentDimension == INIT_DIMENSION){
        currentDimension = INFECTED_DIMENSION;
    }else{
        currentDimension = INIT_DIMENSION;
    }
}

DimensionsType getCurrentDimension(void){
    return currentDimension;
}