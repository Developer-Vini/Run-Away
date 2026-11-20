#ifndef DIMENSION_H
#define DIMENSION_H

typedef enum {
    INIT_DIMENSION,
    INFECTED_DIMENSION
} DimensionsType;

void initDimension(void);
void changeDimension(void);

DimensionsType getCurrentDimension(void);
#endif