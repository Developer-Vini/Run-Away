#include "../include/raylib.h"
#include "../include/camera.h"
#include "../include/world.h"
#include "../include/chunk.h"
#include "../include/weapon.h"

int main(void){

    InitWindow( 1280, 720, "test telça");

    loadTerrainTexture();
    loadTerrainShader();

    DisableCursor();
    SetTargetFPS(60);

    
    GameCamera camera;

    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});


    Weapon weapon = createWeapon();

    while(!WindowShouldClose()){
        
        updateCamera(&camera);
        snapCameraToGround(&camera, 1.7f);
        updateWorld(camera.camera.position);
        updateWeaponAnimation(&weapon);
        updateTerrainShader(camera.camera.position);
        updateWeapon(&weapon);
        BeginDrawing();
            ClearBackground((Color){10, 14, 17, 255});
            initCamera(&camera);
                drawWorld();
                drawWeapon(&weapon, camera.camera);
            finishCamera();
                DrawFPS(10,10);
        EndDrawing();
    }

    unloadWeapon(&weapon);
    unloadWorld();
    unloadTerrainShader();
    unloadTerrainTexture();
    CloseWindow();
    return 0;

}