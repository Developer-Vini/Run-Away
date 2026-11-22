#include "../include/raylib.h"
#include "../include/camera.h"
#include "../include/world.h"
#include "../include/chunk.h"
#include "../include/weapon.h"
#include "../include/door.h"
#include "../include/dimension.h"
#include "../include/menu.h"
#include "../include/cutscene.h"

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_CUTSCENE,
    GAME_STATE_PLAIYING
}GameState;

int main(void){

    InitWindow( 1280, 720, "Run Away");

    InitAudioDevice();
    loadTerrainTexture();
    loadTerrainShader();
    initMenu();

    //DisableCursor();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Door door = {0};

    GameCamera camera;
    Weapon weapon = createWeapon();

    createCamera(&camera, (Vector3){0.0f, 1.7f, 5.0f}, (Vector3){0.0f, 1.7f, 0.0f});
    initDoor(&door);

    Cutscene cutscene = {0};

    //setDimension(INFECTED_DIMENSION);
    initDimension();
    GameState gameState = GAME_STATE_MENU;
    bool shouldQuit = false;

    while(!WindowShouldClose() && !shouldQuit){
        if(gameState == GAME_STATE_MENU){
            MenuAction action = updateMenu();
            if(action == MENU_ACTION_PLAY){
                startCutscene(&cutscene, &camera);
                gameState = GAME_STATE_CUTSCENE;
                DisableCursor();
            }else if(action == MENU_ACTION_QUIT){
                shouldQuit = true;
            }
            BeginDrawing();
                drawMenu();
            EndDrawing();
            continue;
        }

        if(IsKeyPressed(KEY_ESCAPE)){
            gameState = GAME_STATE_MENU;
            EnableCursor();
            continue;
        }

        if(gameState == GAME_STATE_CUTSCENE){
            bool finished = updateCutscene(&cutscene, &camera);

            updateWorld(camera.camera.position);
            updateTerrainShader(camera.camera.position);
            
            BeginDrawing();
                ClearBackground((Color){10, 14, 17, 255});
            
                initCamera(&camera);
                    drawWorld();
                finishCamera();
                
                drawCutscene(&cutscene);
            EndDrawing();
            if(finished){
                gameState = GAME_STATE_PLAIYING;
            }

            continue;
        }

        updateCamera(&camera);
        snapCameraToGround(&camera, 1.7f);
        updateDimension();
        if(didDimensionJustChanged()){
            resetWorld();
            Vector3 spaw = (getCurrentDimension() == INFECTED_DIMENSION) ? (Vector3){0.0f, 1.7f, 0.0f} : (Vector3){0.0f, 1.7f, -26.0f};
            camera.camera.position = spaw;
            camera.camera.target = (Vector3){
                spaw.x, spaw.y, spaw.z + 1.0f
            };
        }
        updateWorld(camera.camera.position);
        updateTerrainShader(camera.camera.position);
        updateDoor(&door, camera.camera.position);
        updateWeapon(&weapon);
        updateWeaponAnimation(&weapon);

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
                    DrawText(door.isUnlocked ? "[F] Open" : "Locked", 20, 60, 23, YELLOW);
                }
                drawDimensionTransition();
        EndDrawing();
    }

    unloadWeapon(&weapon);
    unloadWorld();
    unloadTerrainShader();
    unloadTerrainTexture();
    unloadMenu();
    unloadDoor(&door);
    CloseWindow();
    return 0;

}