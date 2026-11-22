#include "../include/cutscene.h"
#include "../include/raymath.h"

#include <math.h>
#define CUTSCENE_DURATION 4.0f

static float smoothStep(float value){
    value = Clamp(value, 0.0f, 1.0f);
    return value * value * (3.0f - 2.0f * value);
}

void startCutscene(Cutscene *cutscene, GameCamera *camera){
    cutscene->timer = 0.0f;
    cutscene->active = true;

    Vector3 direction = Vector3Subtract(camera->camera.target, camera->camera.position);
    direction.y = 0.0f;

    float lenght = sqrtf(direction.x * direction.x + direction.z * direction.z);

    if(lenght > 0.001f){
        direction.x /= lenght;
        direction.z /= lenght;
    }else{
        direction = (Vector3){0.0f, 0.0f, -1.0f};
    }
    // cutscene->startPosition = (Vector3){
    //     0.0f, gH + 0.65f, 5.0f
    // };

    cutscene->fowardDirection = direction;

    float gH = getTerrainH(camera->camera.position.x, camera->camera.position.z);


    cutscene->startPosition = camera->camera.position;
    cutscene->startPosition.y = gH + 0.65f;

    camera->camera.position = cutscene->startPosition;
    
    // camera->camera.target = (Vector3){
    //     0.0f, -0.35f, camera->camera.position.z - 0.85f
    // };
}

bool updateCutscene(Cutscene *cutscene, GameCamera *camera){
    if(!cutscene->active) return true;
    
    cutscene->timer += GetFrameTime();

    float progress = cutscene->timer / CUTSCENE_DURATION;
    float animation = smoothStep(progress);


    float gH = getTerrainH(cutscene->startPosition.x, cutscene->startPosition.z);

    float cameraH = Lerp(
        gH + 0.65f, gH + 1.7f, animation
    );

    camera->camera.position.y = cameraH;

    float lookY = Lerp(
        gH + 0.38f, gH + 1.60f, animation
    );
    camera->camera.target = (Vector3){
        camera->camera.position.x, lookY,  camera->camera.position.z - 0.85f
    };

    if(cutscene->timer >= CUTSCENE_DURATION){
        cutscene->active = false;
        camera->camera.position.y = gH +  1.7f;

        camera->camera.target = (Vector3){
            camera->camera.position.x, camera->camera.position.y, camera->camera.position.z - 0.85f
        };
        return true;
    }

    return false;

}

void drawCutscene(Cutscene *cutscene){
    if(!cutscene->active) return;

    float alpha = 1.0f - Clamp(cutscene->timer / 1.4, 0.0f, 1.0f);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, (unsigned char)(alpha * 255)});
}