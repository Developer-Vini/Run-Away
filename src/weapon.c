#include "../include/weapon.h"
#include "../include/raymath.h"

#include <stddef.h>

#define ANIMATION_IDLE 0
#define ANIMATION_WALK 1
#define ANIMATION_FIRE 4
#define ANIMATION_RELOAD_PARTIAL 5
#define ANIMATION_RELOAD_EMPTY 6
#define ANIMATION_FRAMES_PER_SECOND 60.0f

#define MAGAZINE_SIZE 20
#define STARTING_RESERVE_AMMO 80
#define ROUND_PER_MINUTE 650.0f
#define IS_AUTO true


static bool isReloading(const Weapon *weapon){
    return weapon->currentAnimation == ANIMATION_RELOAD_PARTIAL || weapon->currentAnimation == ANIMATION_RELOAD_EMPTY;
}

static void playAnimation(Weapon *weapon, int animationIndex){
    weapon->currentAnimation = animationIndex;
    weapon->currentAnimation = 0.0f;
}

static void finishedLoad(Weapon *weapon){
    int missingAmmo = MAGAZINE_SIZE - weapon->magazineAmmo;
    int loadedAmmo = missingAmmo < weapon->reserveAmmo ? missingAmmo : weapon->reserveAmmo;

    weapon->magazineAmmo += loadedAmmo;
    weapon->reserveAmmo -= loadedAmmo;

}

static void playSound(Sound sound){
    if(!IsSoundValid(sound)) return;
    
    SetSoundPitch(sound, GetRandomValue(95, 105) / 100.0f);
    PlaySound(sound);
}

Weapon createWeapon(void){
    Weapon weapon = {0};

    weapon.model = LoadModel("assets/3Dmodels/fps_animations_vsk.glb");

    weapon.animations = LoadModelAnimations("assets/3Dmodels/fps_animations_vsk.glb", &weapon.animationsCount);

    for(int i = 0; i < weapon.animationsCount; i++){
        if(!IsModelAnimationValid(weapon.model, weapon.animations[i])){

            TraceLog(LOG_WARNING, "anmicacao %d (%s) nao combina com o modelo", i, weapon.animations[i].name);
        }
    }

    weapon.armsMeshI = 0;
    for(int i = 0; i < weapon.model.meshCount; i++){
        TraceLog(LOG_INFO, "malha %d: %d vertices", i, weapon.model.meshes[i].vertexCount);

        if(weapon.model.meshes[i].vertexCount > weapon.model.meshes[weapon.armsMeshI].vertexCount){
            weapon.armsMeshI = i;
        }
    }

    weapon.shader = LoadShader("assets/weapon.vs", "assets/weapon.fs");
    weapon.vPositionLocation = GetShaderLocation(weapon.shader, "viewPos");

    for(int i = 0; i < weapon.model.materialCount; i++){
        weapon.model.materials[i].shader = weapon.shader;
    }

    TraceLog(LOG_INFO, "animacoes carregadas: %d", weapon.animationsCount);

    TraceLog(LOG_INFO, "marma: meshes=%d materials=%d", weapon.model.meshCount, weapon.model.materials);

    weapon.offsetFromCamera = (Vector3){
        0.053f, -0.260f, 0.287f
    };
    weapon.correctionAngles = (Vector3){
        270.0f, 0.0f, 0.0f
    };
    weapon.scale = 0.0045f;

    return weapon;
}

void updateWeapon(Weapon *weapon){

    static bool isAdjustOn = false;

    if(IsKeyPressed(KEY_F1)){
        isAdjustOn = !isAdjustOn;
        TraceLog(LOG_INFO, "ajuste: %s", isAdjustOn ? "LIGADO" : "DESLIGADO");
    }

    if(!isAdjustOn) return;

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

    Matrix scaleMatrix = MatrixScale(weapon->scale, weapon->scale, weapon->scale);
    Matrix translationMatrix = MatrixTranslate(position.x, position.y, position.z);
    Matrix finalTransform = MatrixMultiply(weapon->model.transform, MatrixMultiply(scaleMatrix, translationMatrix));


    float cameraPosition[3] = {
        camera.position.x,
        camera.position.y,
        camera.position.z,
    };
    SetShaderValue(weapon->shader, weapon->vPositionLocation, cameraPosition, SHADER_UNIFORM_VEC3);


    for(int i = 0; i < weapon->model.meshCount; i++){
        if(i == weapon->armsMeshI) continue;

        Material material = weapon->model.materials[weapon->model.meshMaterial[i]];
        DrawMesh(weapon->model.meshes[i], material, finalTransform);
    }
    //DrawModel(weapon->model, position, weapon->scale, WHITE);
}

void unloadWeapon(Weapon *weapon){
    UnloadModelAnimations(weapon->animations, weapon->animationsCount);
    
    for(int i = 0; i <weapon->model.materialCount; i++){
        weapon->model.materials[i].shader.id = 0;
        weapon->model.materials[i].shader.locs = NULL;
    }
    
    UnloadModel(weapon->model);
    UnloadShader(weapon->shader);
}


void updateWeaponAnimation(Weapon *weapon){
    if(weapon->animationsCount == 0) return;

    bool isBusy = weapon->currentAnimation == ANIMATION_FIRE || weapon->currentAnimation == ANIMATION_RELOAD;
    
    if(!isBusy && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        weapon->currentAnimation = ANIMATION_FIRE;
        weapon->currentFrame = 0;
    }else if(!isBusy && IsKeyPressed(KEY_R)){
        weapon->currentAnimation = ANIMATION_RELOAD;
        weapon->currentFrame = 0;
    }

    ModelAnimation animation = weapon->animations[weapon->currentAnimation];
    weapon->currentFrame++;

    if(weapon->currentFrame >= animation.keyframeCount){
        weapon->currentFrame = 0;

        bool isMoving = IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D);

        weapon->currentAnimation = isMoving ? ANIMATION_WALK : ANIMATION_IDLE;
    }

    if(!isBusy){
        bool isMoving = IsKeyDown(KEY_W) || IsKeyDown(KEY_A) || IsKeyDown(KEY_S) || IsKeyDown(KEY_D);

        int wanted = isMoving ? ANIMATION_WALK : ANIMATION_IDLE;
        if(weapon->currentAnimation != wanted){
            weapon->currentAnimation = wanted;
            weapon->currentFrame = 0;
        }
    }


    UpdateModelAnimation(weapon->model, weapon->animations[weapon->currentAnimation], weapon->currentFrame);

}