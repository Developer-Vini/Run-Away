#ifndef CHAO_H
#define CHAO_H

#include "../include/raylib.h"

typedef struct {
    Vector3 center;
    Vector2 size; 
    Color color;
    /* data */
} Floor;


Floor createFloor(float centerX, float centerY, float centerZ, float sizeX, float sizeY, Color color);
void drawFloor(Floor floor);



#endif