#include "../include/cutscene.h"
#include "../include/raymath.h"
#include "../include/chunk.h"
#define CUTSCENE_DURATION 4.0f

static float smoothStep(float value){
    value = Clamp(value, 0.0f, 1.0f);
    return value * value * (3.0f - 2.0f * value);
}

void startCutscene(Cutscene *cutscene, GameCamera *camera){
    float gH = getTerrainH(0.0f, 5.0f);

    cutscene->timer = 0.0f;
    cutscene->active = true;

    cutscene->startPosition = (Vector3){
        0.0f, gH + 0.65f, 5.0f
    };

    camera->camera.position = cutscene->startPosition;
    
    camera->camera.target = (Vector3){
        0.0f, -0.35f, camera->camera.position.z - 0.85f
    };
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