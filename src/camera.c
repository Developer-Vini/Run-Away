#include "../include/camera.h"

void createCamera(gameCamera *GC, Vector3 position, Vector3 target, Vector3 up){
    int fovy = 45.0f;
    int projection = CAMERA_PERSPECTIVE;

    GC->camera.position = position;
    GC->camera.target = target;
    GC->camera.up = up;

    GC->camera.fovy = fovy;
    GC->camera.projection = projection;

}

void updateCamera(gameCamera *UCG){
    UpdateCamera(&UCG->camera, UCG->cameraMode);
}