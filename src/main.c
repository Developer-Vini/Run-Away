#include "../include/raylib.h"
#include "../include/camera.h"
#include "../include/world.h"
#include "../include/chunk.h"
int main(void){

    InitWindow( 1280, 720, "test telça");

    loadTerrainTexture();

    DisableCursor();
    SetTargetFPS(60);

    GameCamera camera;

    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});

    while(!WindowShouldClose()){
        
        updateCamera(&camera);
        snapCameraToGround(&camera, 1.7f);
        updateWorld(camera.camera.position);
        BeginDrawing();
            ClearBackground(SKYBLUE);
            initCamera(&camera);
                drawWorld();
            finishCamera();
                DrawFPS(10,10);
        EndDrawing();
    }

    unloadWorld();
    unloadTerrainTexture();
    CloseWindow();
    return 0;

}