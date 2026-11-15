#include "../include/raylib.h"
#include "../include/floor.h"
#include "../include/camera.h"

int main(void){

    InitWindow( 800, 350, "test telça");
    DisableCursor();
    SetTargetFPS(60);

    Floor mainFloor = createFloor(0.0f, 0.0f, 0.0f, 10.0f, 10.0f, DARKGRAY);
    GameCamera camera;
    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});

    while(!WindowShouldClose()){
        
        updateCamera(&camera);

        BeginDrawing();
            ClearBackground(BLACK);
            initCamera(&camera);
                drawFloor(mainFloor);
                //DrawPlane((Vector3){0, 0, 0}, (Vector2){30,30}, DARKGRAY);
                DrawCube((Vector3){ -4, 1, 0}, 2, 2, 2, RED);
                DrawCubeWires((Vector3){ -4, 1, 0}, 2, 2, 2, GREEN);
                DrawSphere((Vector3){0, 1, -6}, 1.0f, GREEN);
            finishCamera();
                DrawFPS(10,10);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}