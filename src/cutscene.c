#include "../include/cutscene.h"
#include "../include/raymath.h"

#define CUTSCENE_DURATION 4.0f

static float smoothStep(float value){
    value = Clamp(value, 0.0f, 1.0f);
    return value * value * (3.0f - 2.0f * value);
}

void startCutscene(Cutscene *cutscene, GameCamera *camera){
    cutscene->timer = 0.0f;
    cutscene->active = true;

    cutscene->startPosition = (Vector3){
        0.0f, 0.24f, 5.0f
    };

    camera->camera.position = cutscene->startPosition;
    
    camera->camera.target = (Vector3){
        0.0f, -0.20f, 5.90
    };
}

bool updateCutscene(Cutscene *cutscene, GameCamera *camera){
    if(!cutscene->active) return true;

    float progress = cutscene->timer / CUTSCENE_DURATION;
    float animation = smoothStep(progress);

    cutscene->timer += GetFrameTime();

    float cameraH = Lerp(
        0.18f, 1.7f, animation
    );

    camera->camera.position.y = cameraH;

    float lookY = Lerp(
        -0.38f, 1.60f, animation
    );
    camera->camera.target = (Vector3){
        0.0f, lookY, 5.90
    };

    if(cutscene->timer >= CUTSCENE_DURATION){
        cutscene->active = false;
        camera->camera.position.y = 1.7f;

        camera->camera.target = (Vector3){
            0.0f, 1.5f, 5.90
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