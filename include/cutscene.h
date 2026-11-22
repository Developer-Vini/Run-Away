#ifndef CUTSCENE_H
#define CUTSCENE_H

#include "raylib.h"
#include "camera.h"
#include "chunk.h"

typedef enum {
    CUTSCENE_WAKE,
    CUTSCENE_DOOR_DISCOVERY,
} CutsceneType;

typedef struct {
    float timer;
    bool active;
    Vector3 startPosition;
    Vector3 fowardDirection;

    CutsceneType type;
} Cutscene;

void startCutscene(Cutscene *cutscene, GameCamera *camera);
bool updateCutscene(Cutscene *cutscene, GameCamera *camera);
void drawCutscene(Cutscene *cutscene);

void startDoorCutscene(Cutscene *cutscene, GameCamera *camera);

#endif