#include "../include/camera.h"

void createCamera(GameCamera *GC, Vector3 position, Vector3 target){
    int fovy = 45.0f;
    int projection = CAMERA_PERSPECTIVE;
    int mode = CAMERA_FIRST_PERSON;

    GC->camera.position = position;
    GC->camera.target = target;
    GC->camera.up = (Vector3){0.0f, 1.0f, 0.0f};

    GC->camera.fovy = fovy;
    GC->camera.projection = projection;


    GC->cameraMode = mode;

}

void updateCamera(GameCamera *UCG){
    UpdateCamera(&UCG->camera, UCG->cameraMode);
}

void initCamera(GameCamera *IGC){
    BeginMode3D(IGC->camera);
}

void finishCamera(void){
    EndMode3D();
}
