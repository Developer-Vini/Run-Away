#include "../include/door.h"
#include "../include/dimension.h"

#include <math.h>

void initDoor(Door *door){
    door->position = (Vector3){
        0.0f, 0.0f, -29.0f
    };
    door->scale = (Vector3){
        1.0f, 1.0f, 1.0f 
    };

    door->rotationAngle = 0.0f;
    door->interactionRadius = 2.0f;
    door->canInteract = false;

    door->model = LoadModel("assets/3Dmodels/door_2_loose.glb");

    door->loaded = door->model.meshCount > 0;

    door->isUnlocked = false;
}

void updateDoor(Door *door, Vector3 playerPosition){
    if(getCurrentDimension() != INIT_DIMENSION){
        door->canInteract =  false;
        return;
    }

    float distanceX = playerPosition.x - door->position.x;
    float distanceZ = playerPosition.z - door->position.z;
    float distance = sqrtf(distanceX * distanceX + distanceZ * distanceZ);

    door->canInteract = distance <= door->interactionRadius;

    if(door->canInteract && door->isUnlocked && IsKeyPressed(KEY_F) && !isDimensionTras()){
        changeDimension();
    }
}

void drawDoor(Door *door){
    if(!door->loaded || getCurrentDimension() != INIT_DIMENSION) return;
    DrawModelEx(door->model, door->position, (Vector3){0.0f, 1.0f, 0.0f}, door->rotationAngle, door->scale, WHITE);
}

void unloadDoor(Door *door){
    if(door->loaded){
        UnloadModel(door->model);
        door->loaded = false;
    }
}