#ifndef HOUSE_EVENT_H
#define HOUSE_EVENT_H

#include "camera.h"

typedef enum{
    HOUSE_EVENT_IDLE,
    HOUSE_EVENT_EPLORING,
    HOUSE_EVENT_DIZZY,
    HOUSE_EVENT_BLINKING,
    HOUSE_EVENT_UNCONSCIOUS,
    HOUSE_EVENT_WAITING_DIMENSTION,
    HOUSE_EVENT_FINISHED
} HouseEventState;

typedef struct {
    HouseEventState state;
    /* data */
} HouseEvent;

void startHouseEvent(HouseEvent *event, GameCamera *camera);


#endif