#ifndef CAMERA_H
#define CAMERA_H

#include "../include/raylib.h"

typedef struct{
    Camera3D camera;
    int mode;
} gameCamera;

void createCamera(gameCamera *GC, Vector3 position, Vector3 target, Vector3 up);

#endif