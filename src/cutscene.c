#include "../include/cutscene.h"
#include "../include/raymath.h"

#define CUTSCENE_DURATION 4.0f

void startCutscene(Cutscene *cutscene, GameCamera *camera){
    cutscene->timer = 0.0f;
    cutscene->active = true;

    cutscene->startPosition = (Vector3){
        0.0f, 0.24f, 5.0f
    };

    camera->camera.position = cutscene->startPosition;
    
    camera->camera.target = (Vector3){
        0.0f, -0.20f, 5.90
    };
}