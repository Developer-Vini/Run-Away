#include "../include/weapon.h"
#include "../include/raymath.h"

Weapon createWeapon(void){
    Weapon weapon = {0};

    weapon.model = LoadModel("assets/3Dmodels/fps_animations_vsk.glb");

    TraceLog(LOG_INFO, "marma: meshes=%d materials=%d", weapon.model.meshCount, weapon.model.materials);

    weapon.offsetFromCamera = (Vector3){
        0.0f, 0.0f, 0.0f
    };
    weapon.correctionAngles = (Vector3){
        0.0f, 0.0f, 0.0f
    };
    weapon.scale = 1.0f;

    return weapon;
}

void updateWeapon(Weapon *weapon){
    float deltaTime = GetFrameTime();
    float moveStep = 0.5f * deltaTime;

    if(IsKeyPressed(KEY_ONE)) {
        weapon->correctionAngles.x += 90.0f;
    }
    
    if(IsKeyPressed(KEY_TWO)) {
        weapon->correctionAngles.y += 90.0f;
    }
    
    if(IsKeyPressed(KEY_THREE)) {
        weapon->correctionAngles.z += 90.0f;
    }


    if(IsKeyDown(KEY_EQUAL)){
        weapon->scale *= 1.0f + 2.0f * deltaTime;
    }
    if(IsKeyDown(KEY_MINUS)){
        weapon->scale /= 1.0f + 2.0f * deltaTime;
    }

    if(IsKeyDown(KEY_RIGHT)){
        weapon->offsetFromCamera.x += moveStep;
    }
        if(IsKeyDown(KEY_LEFT)){
        weapon->offsetFromCamera.x -= moveStep;
    }
        if(IsKeyDown(KEY_UP)){
        weapon->offsetFromCamera.y += moveStep;
    }
        if(IsKeyDown(KEY_DOWN)){
        weapon->offsetFromCamera.y -= moveStep;
    }
        if(IsKeyDown(KEY_PAGE_UP)){
        weapon->offsetFromCamera.z += moveStep;
    }
        if(IsKeyDown(KEY_PAGE_DOWN)){
        weapon->offsetFromCamera.z -= moveStep;
    }

    if(IsKeyPressed(KEY_P)){
        TraceLog(LOG_INFO, "arma: giro=(%.0f,%.0f,%.0f) escala=%.4f offset=(%.3f,%.3f,%.3f)", weapon->correctionAngles.x, weapon->correctionAngles.y, weapon->correctionAngles.z, weapon->scale, weapon->offsetFromCamera.x, weapon->offsetFromCamera.y, weapon->offsetFromCamera.z);
    }
}

void drawWeapon(Weapon *weapon, Camera3D camera){
    Vector3 foward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    Vector3 right = Vector3Normalize(Vector3CrossProduct(foward, camera.up));
    Vector3 up = Vector
}