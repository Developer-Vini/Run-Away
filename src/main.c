#include "../include/raylib.h"
#include "../include/floor.h"
#include "../include/camera.h"
#include "../include/chunk.h"

int main(void){

    InitWindow( 800, 350, "test telça");
    DisableCursor();
    SetTargetFPS(60);

    Floor mainFloor = createFloor(0.0f, 0.0f, 0.0f, 10.0f, 10.0f, DARKGRAY);
    GameCamera camera;
    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});

    Chunk chunk = createChunk(0, 0);
    Chunk chunk2 = createChunk(1, 0);
Chunk chunk3 = createChunk(2, 0);
    while(!WindowShouldClose()){
        
        updateCamera(&camera);

        BeginDrawing();
            ClearBackground(BLACK);
            initCamera(&camera);
                drawFloor(mainFloor);
                drawChunk(&chunk);
                drawChunk(&chunk2);
                drawChunk(&chunk3);
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