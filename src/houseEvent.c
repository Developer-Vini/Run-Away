#include "../include/houseEvent.h"
#include <math.h>

static float blinkPulse(float time, float start, float closeTime, float openTime){
    if(time < start) return 0.0f;

    float elapsed = time - start;

    if(elapsed < closeTime){
        return elapsed / closeTime;
    }

    if(openTime <= 0.0f) return 1.0f;

    elapsed -= closeTime;

    if(elapsed < openTime){
        return elapsed / openTime;
    }

    return 0.0f;
}
void startHouseEvent(HouseEvent *event, GameCamera *camera){
    event->state = HOUSE_EVENT_EPLORING;
    event->timer = 0.0f;

    event->originalPosition = camera->camera.position;
    event->origianlTarget = camera->camera.target;
}

