#ifndef CAMERA_H
#define CAMERA_H

#include "../include/raylib.h"
#include "../include/raymath.h"

typedef struct{
    Camera3D camera;
    int cameraMode;

    //float mouseSesi;
    //float moviSpeed;
} GameCamera;

void createCamera(GameCamera *GC, Vector3 position, Vector3 target);
void updateCamera(GameCamera *UGC);
void initCamera(GameCamera *IGC);
void snapCameraToGround(GameCamera *GC, float eyeH);
void finishCamera(void);
#endif