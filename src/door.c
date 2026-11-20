#include "../include/door.h"
#include "../include/dimension.h"

void initDoor(Door *door){
    door->position = (Vector3){
        0.0f, 0.0f, 7.0f
    };
    door->interactionRadius = 2.0f;
    door->canInteract = false;
}