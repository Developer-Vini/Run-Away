#include "../include/floor.h"

Floor createFloor(float centerX, float centerY, float centerZ, float sizeX, float sizeY, Color color){

    Floor newFloor;

    newFloor.center = (Vector3){centerX, centerY, centerZ};
    newFloor.size = (Vector2){sizeX, sizeY};
    newFloor.color = color;

    return newFloor;

}

void drawFloor(Floor floor){
    
    
    DrawPlane(floor.center, floor.size, floor.color);

    //chao 2d kakaakak
    //DrawRectangleRec(floor.rectangle, floor.color);
}