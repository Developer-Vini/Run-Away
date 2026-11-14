#ifndef CHAO_H
#define CHAO_H

#include "raylib.h"

typedef struct {
    Rectangle rectangle;
    Color color;
    /* data */
} Floor;

Floor createFloor(float x, float y, float width, float height, Color color);
void drawFloor(Floor floor)


#endif