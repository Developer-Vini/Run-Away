#ifndef DOOR_H
#define DOOR_H

#include "raylib.h"
#include "raymath.h"

typedef struct{
    Vector3 position;
    float interactionRadius;
    bool canInteract;
    /* data */
} Door;

void initDoor(Door *door);
void updateDoor(Door *door, Vector3 playerPosition);

#endif