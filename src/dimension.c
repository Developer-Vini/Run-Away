#include "../include/dimension.h"

static DimensionsType currentDimension = INIT_DIMENSION;
static float transitionAlpha = 0.0f;
static bool transition = false;
static bool changig = false;

void initDimension(void){
    currentDimension = INIT_DIMENSION;
    transitionAlpha = 0.0f;
    transition = false;
    changig = false;
}

void changeDimension(void){
    if(transition) return;

    transition = true;
    changig = false;
}

void updateDimension(void){
    if(!transition) return;

    transitionAlpha += GetFrameTime() * 1.4f;

    if(transitionAlpha >= 1.0f && !changig){
        transitionAlpha = 1.0f;
        if(currentDimension == INIT_DIMENSION){
            currentDimension = INFECTED_DIMENSION;
        }else{
            currentDimension = INIT_DIMENSION;
        }

        changig = true;
    }

    if(changig){
        transitionAlpha -= GetFrameTime() * 1.4f;
        if(transitionAlpha <= 0.0f){
            transitionAlpha = 0.0f;
            transition = false;
            changig = false;
        }
    }
}

void drawDimensionTransition(void){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, (unsigned char)(transitionAlpha * 255.0f)});
}

bool isDimensionTras(void){
        return transition;
}
DimensionsType getCurrentDimension(void){
    return currentDimension;
}