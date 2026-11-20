#include "../include/door.h"
#include "../include/dimension.h"

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
}

void updateDoor(Door *door, Vector3 playerPosition){
    float distance = Vector3Distance(playerPosition, door->position);

    door->canInteract = distance <= door->interactionRadius;

    if(door->canInteract && IsKeyPressed(KEY_F)){
        changeDimension();
    }
}

void drawDoor(Door *door){
    if(!door->loaded) return;
    DrawModelEx(door->model, door->position, (Vector3){0.0f, 1.0f, 0.0f}, door->rotationAngle, door->scale, WHITE);
}

void unloadDoor(Door *door){
    if(door->loaded){
        UnloadModel(door->model);
        door->loaded = false;
    }
}