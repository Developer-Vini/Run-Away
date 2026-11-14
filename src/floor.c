#include "../include/floor.h"

Floor createFloor(float x, float y, float width, float height, Color color){

    Floor newFloor;

    newFloor.rectangle = (Rectangle){x, y, width, height};
    newFloor.color = color;

    return newFloor;

}

void drawFloor(Floor floor){
    DrawRectangleRec(floor.rectangle, floor.color);
}