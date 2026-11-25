#include "../include/houseEvent.h"

void startHouseEvent(HouseEvent *event, GameCamera *camera){
    event->state = HOUSE_EVENT_EPLORING;
    event->timer = 0.0f;

    event->originalPosition = camera->camera.position;
    event->origianlTarget = camera->camera.target;
}