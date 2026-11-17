#ifndef WORLD_H
#define WORLD_H

#include "../include/raylib.h"

void initWorld(void);
void updateWorld(Vector3 playerPosition);
void drawWorld(void);
void unloadWorld(void);

#endif