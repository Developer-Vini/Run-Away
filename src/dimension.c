#include "../include/dimension.h"

static DimensionsType currentDimension = INIT_DIMENSION;
static float transitionAlpha = 0.0f;
static bool transition = false;
static bool dimensionJustChange = false;
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

    //TraceLog(LOG_INFO, "changeDimension chamado");
}

void updateDimension(void){
    if(!transition) return;

    float  fadeStep = GetFrameTime() * 1.4f;

    if(!changig){
        transitionAlpha += fadeStep;
        if(transitionAlpha >= 1.0f){
            transitionAlpha = 1.0f;
            currentDimension = (currentDimension == INIT_DIMENSION) ? INFECTED_DIMENSION : INIT_DIMENSION;
            changig = true;
            dimensionJustChange = true;

            //TraceLog(LOG_INFO, "dimensao trocada para %d", currentDimension);
        }
    } else{
        transitionAlpha -= fadeStep;
        if(transitionAlpha <= 0.0f){
            transitionAlpha = 0.0f;
            //currentDimension = (currentDimension == INIT_DIMENSION) ? INFECTED_DIMENSION : INIT_DIMENSION;
            changig = false;
            transition = false;
            dimensionJustChange =false;
            //TraceLog(LOG_INFO, "transicao terminou");
        }
    }
}

void drawDimensionTransition(void){
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, (unsigned char)(transitionAlpha * 255.0f)});
}

bool isDimensionTras(void){
        return transition;
}
bool didDimensionJustChanged(void){
    bool result = dimensionJustChange;
    dimensionJustChange = false;
    return result;
}
DimensionsType getCurrentDimension(void){
    return currentDimension;
}