#include "../include/door.h"
#include "../include/dimension.h"

#include <math.h>

void initDoor(Door *door){
    door->position = (Vector3){
        0.0f, 0.0f, 7.0f
    };
    door->interactionRadius = 2.0f;
    door->canInteract = false;
}

void updateDoor(Door *door, Vector3 playerPosition){
    float distance = Vector3Distance(playerPosition, door->position);

    door->canInteract = distance <= door->interactionRadius;

    if(door->canInteract && IsKeyPressed(KEY_E)){
        changeDimension();
    }
}