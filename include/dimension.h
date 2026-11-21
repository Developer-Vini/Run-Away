#ifndef DIMENSION_H
#define DIMENSION_H

#include "raylib.h"

typedef enum {
    INIT_DIMENSION,
    INFECTED_DIMENSION
} DimensionsType;

void initDimension(void);
void changeDimension(void);

void updateDimension(void);
void drawDimensionTransition(void);
bool isDimensionTras(void);
bool didDimensionJustChanged(void);

void setDimension(DimensionsType dimension);

DimensionsType getCurrentDimension(void);
#endif