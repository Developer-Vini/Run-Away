#include "../include/cutscene.h"
#include "../include/raymath.h"

#include <math.h>
#define CUTSCENE_DURATION 10.0f

static float smoothStep(float value){
    value = Clamp(value, 0.0f, 1.0f);
    return value * value * (3.0f - 2.0f * value);
}

void startCutscene(Cutscene *cutscene, GameCamera *camera){
    cutscene->timer = 0.0f;
    cutscene->active = true;

    cutscene->type = CUTSCENE_WAKE;

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

    float progress = Clamp(cutscene->timer / CUTSCENE_DURATION, 0.0f, 1.0f);
    float animation = smoothStep(progress);


    float gH = getTerrainH(cutscene->startPosition.x, cutscene->startPosition.z);

    float cameraH = Lerp(
        gH + 0.65f, gH + 1.7f, animation
    );

    camera->camera.position.y = cameraH;

    // float lookY = Lerp(
    //     gH + 0.38f, gH + 1.60f, animation
    // );

    float yaw = 0.0f;  //sinf(cutscene->timer * 1.8f) * 0.65;

    if(cutscene->timer >= 2.0f && cutscene->timer < 3.0f){
        yaw = Lerp(0.0f, 0.45, smoothStep((cutscene->timer - 2.0f))); // 2.0f));
    }else if(cutscene->timer >= 3.0f && cutscene->timer < 4.0f){
        // yaw = Lerp(0.0f, 0.45, smoothStep((cutscene->timer - 4.0f) / 2.0f));
        yaw = 0.45f;
    }else if(cutscene->timer >= 4.0f && cutscene->timer < 6.0f){
        yaw = Lerp(0.45f, -0.45f, smoothStep((cutscene->timer - 4.0f) / 2.0f));
    }else if(cutscene->timer >= 6.0f && cutscene->timer < 7.0f){
        //yaw = Lerp(0.45f, -0.45f, smoothStep((cutscene->timer - 8.0f) / 2.5f));
        yaw = -0.45f;
    }else if(cutscene->timer >= 7.0f){
        yaw = Lerp(-0.45f, 0.0f, smoothStep((cutscene->timer - 7.0f) / 3.0f));
    }

    Vector3 direction = cutscene->fowardDirection;

    float cosYaw = cosf(yaw);
    float sinYaw = sinf(yaw);

    Vector3 rotateDirection = {
        direction.x * cosYaw + direction.z * sinYaw, 0.0f, -direction.x * sinYaw + direction.z * cosYaw 
    };

    camera->camera.target = (Vector3){
        camera->camera.position.x + rotateDirection.x, camera->camera.position.y - 0.05f,  camera->camera.position.z + rotateDirection.z
    };


    if(progress >= 1.0f){
        cutscene->active = false;
        camera->camera.position.y = gH +  1.7f;

        camera->camera.target = (Vector3){
            camera->camera.position.x + direction.x, camera->camera.position.y, camera->camera.position.z + direction.z
        };
        return true;
    }

    return false;

}

void startDoorCutscene(Cutscene *cutscene, GameCamera *camera){
    cutscene->timer = 0.0f;
    cutscene->active = true;

    cutscene->type = CUTSCENE_WAKE;

    Vector3 direction = Vector3Subtract(camera->camera.target, camera->camera.position);
    direction.y = 0.0f;

    float lenght = Vector3Length(direction);

    if(lenght > 0.001f){
        direction = Vector3Scale(direction, 1.0f /lenght);
    }else{
        direction = (Vector3){0.0f, 0.0f, -1.0f};
    }   

    cutscene->fowardDirection = direction;
    cutscene->startPosition = camera->camera.position;


}

void drawCutscene(Cutscene *cutscene){
    if(!cutscene->active) return;

    float alpha = 1.0f - Clamp(cutscene->timer / 1.4, 0.0f, 1.0f);

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, (unsigned char)(alpha * 255)});
}