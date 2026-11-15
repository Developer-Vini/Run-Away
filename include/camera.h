#ifndef CAMERA_H
#define CAMERA_H

#include "../include/raylib.h"

typedef struct{
    Camera3D camera;
    int cameraMode;
} gameCamera;

void createCamera(gameCamera *GC, Vector3 position, Vector3 target, Vector3 up);
void updateCamera(gameCamera *UGC);
#endif