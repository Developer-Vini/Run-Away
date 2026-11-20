#ifndef DOOR_H
#define DOOR_H

#include "raylib.h"
#include "raymath.h"

typedef struct{
    Model model;
    Vector3 scale;
    Vector3 position;
    float rotationAngle;
    float interactionRadius;
    bool canInteract;
    bool loaded;
    /* data */
} Door;

void initDoor(Door *door);
void updateDoor(Door *door, Vector3 playerPosition);
void drawDoor(Door *door);
void unloadDoor(Door *door);
#endif