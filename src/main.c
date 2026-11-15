#include "../include/raylib.h"
#include "../include/floor.h"

int main(void){

    InitWindow( 800, 350, "test telça");
    DisableCursor();
    SetTargetFPS(60);

    Floor mainFloor = createFloor(0.0f, 0.0f, 0.0f, 10.0f, 10.0f, DARKGRAY);

    Camera3D camera = { 0 }; 
    camera.position = (Vector3){ 0.0f, 1.7f, 5.0f};
    camera.target = (Vector3){0.0f, 1.7f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 70.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    while(!WindowShouldClose()){
        
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode3D(camera);
                drawFloor(mainFloor);
                //DrawPlane((Vector3){0, 0, 0}, (Vector2){30,30}, DARKGRAY);
                DrawCube((Vector3){ -4, 1, 0}, 2, 2, 2, RED);
                DrawCubeWires((Vector3){ -4, 1, 0}, 2, 2, 2, GREEN);
                DrawSphere((Vector3){0, 1, -6}, 1.0f, GREEN);
            EndMode3D();
                DrawFPS(10,10);

        EndDrawing();
    }

    CloseWindow();
    return 0;

}