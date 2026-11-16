#include "../include/camera.h"
#include "../include/chunk.h"

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

void snapCameraToGround(GameCamera *GC, float eyeH){
    float groundH = getTerrainH(GC->camera.position.x, GC->camera.position.z);
    float newY = groundH + eyeH;

    float diference = newY - GC->camera.position.y;
    GC->camera.position.y += diference;
    GC->camera.target.y += diference;
}
