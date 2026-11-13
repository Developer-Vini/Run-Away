#include "../include/raylib.h"

int main(void){

    InitWindow( 800, 350, "test telça");

    SetTargetFPS(60);

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("teste telinha em raylib", 20, 20, 10, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}