#ifndef DOOR_H
#define DOOR_H

#include "raylib.h"

typedef struct{
    Vector3 position;
    float interactionRadius;
    bool canInteract;
    /* data */
} Door;

void initDoor(Door *door)


#endif