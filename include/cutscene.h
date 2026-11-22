#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "raylib.h"
#include "camera.h"

typedef struct {
    float timer;
    bool active;
    Vector3 startPosition;
} Cutscene;

void startCutscene(Cutscene *cutscene, GameCamera *camera);
bool updateCutscene(Cutscene *cutscene, GameCamera *camera);
void drawCutscene(Cutscene *cutscene);
#endif