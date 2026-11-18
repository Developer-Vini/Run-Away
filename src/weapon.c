#include "../include/weapon.h"
#include "../include/raymath.h"

Weapon createWeapon(void){
    Weapon weapon = {0};

    weapon.model = LoadModel("assets/3Dmodels/fps_animations_vsk.glb");

    TraceLog(LOG_INFO, "marma: meshes=%d materials=%d", weapon.model.meshCount, weapon.model.materials);

    weapon.offsetFromCamera = (Vector3){
        0.158f, -0.125f, 0.717f
    };
    weapon.correctionAngles = (Vector3){
        90.0f, 180.0f, 180.0f
    };
    weapon.scale = 0.7f;

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
    Vector3 up = Vector3CrossProduct(right, foward);

    Vector3 position = camera.position;

    position = Vector3Add(position, Vector3Scale(right, weapon->offsetFromCamera.x));    
    position = Vector3Add(position, Vector3Scale(up, weapon->offsetFromCamera.y));
    position = Vector3Add(position, Vector3Scale(foward, weapon->offsetFromCamera.z));

    float yaw = atan2f(foward.x, foward.z);
    float pitch = -asinf(foward.y);

    Vector3 corectionRadians = {
        weapon->correctionAngles.x * DEG2RAD,
        weapon->correctionAngles.y * DEG2RAD,
        weapon->correctionAngles.z * DEG2RAD
    };

    Matrix corection = MatrixRotateXYZ(corectionRadians);
    Matrix cameraRotaion = MatrixMultiply(MatrixRotateX(pitch), MatrixRotateY(yaw));
    weapon->model.transform = MatrixMultiply(corection, cameraRotaion);

    DrawModel(weapon->model, position, weapon->scale, WHITE);
}

void unloadWeapon(Weapon *weapon){
    UnloadModel(weapon->model);
}