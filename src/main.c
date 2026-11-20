#include "../include/raylib.h"
#include "../include/camera.h"
#include "../include/world.h"
#include "../include/chunk.h"
#include "../include/weapon.h"
#include "../include/door.h"
#include "../include/dimension.h"

int main(void){

    InitWindow( 1280, 720, "test telça");

    InitAudioDevice();
    loadTerrainTexture();
    loadTerrainShader();

    DisableCursor();
    SetTargetFPS(60);

    Door door;
    GameCamera camera;
    Weapon weapon = createWeapon();

    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});
    initDoor(&door);

    while(!WindowShouldClose()){
        
        updateCamera(&camera);
        snapCameraToGround(&camera, 1.7f);
        updateWorld(camera.camera.position);
        updateWeaponAnimation(&weapon);
        updateTerrainShader(camera.camera.position);
        updateWeapon(&weapon);
        updateDoor(&door, camera.camera.position);
        updateDimension();
        bool dFire = updateWeaponFiring(&weapon);
        (void)dFire;
        BeginDrawing();
            ClearBackground((Color){10, 14, 17, 255});
            initCamera(&camera);
            drawWorld();
            drawDoor(&door);
                drawWeapon(&weapon, camera.camera);
            finishCamera();
                DrawText(TextFormat("%d / %d", weapon.magazineAmmo, weapon.reserveAmmo), GetScreenWidth() - 120, GetScreenHeight() - 26, 30, RAYWHITE);
                DrawFPS(10,10);
                if(door.canInteract){
                    DrawText("PRESS F TO INTERACT", 20, 60, 23, YELLOW);
                }
                drawDimensionTransition();
        EndDrawing();
    }

    unloadWeapon(&weapon);
    unloadWorld();
    unloadTerrainShader();
    unloadTerrainTexture();
    unloadDoor(&door);
    CloseWindow();
    return 0;

}