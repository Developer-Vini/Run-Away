#include "../include/raylib.h"
#include "../include/camera.h"
#include "../include/world.h"
#include "../include/chunk.h"
#include "../include/weapon.h"
#include "../include/door.h"
#include "../include/dimension.h"
#include "../include/menu.h"
#include "../include/cutscene.h"
#include "../include/raymath.h"
#include "../include/darkness.h"
#include "../include/floor.h"
#include "../include/houseW.h"
#include <stdio.h>

typedef enum {
    GAME_STATE_MENU,
    GAME_STATE_CUTSCENE,
    GAME_STATE_PLAIYING
}GameState;

static void keepPlayerOutWalls(GameCamera *gameCarema){
    float x = gameCarema->camera.position.x;
    float z = gameCarema->camera.position.z;
    float oldX = x;
    float oldZ = z;

    for(int i = 0; i <HOUSE_WALL_COUNT; i++){
        HouseWall wall = HouseWalls[i];

        float minX = fminf(wall.x1, wall.x2) - 0.5f;
        float maxX = fmaxf(wall.x1, wall.x2) + 0.5f;
        float minZ = fminf(wall.z1, wall.z2) - 0.5f;
        float maxZ = fmaxf(wall.z1, wall.z2) + 0.5f;

        if(x > minX && x < maxX && z > minZ && z < maxZ ){
            float toMinX = x - minX;
            float toMaxX = maxX - x;
            float toMinZ = z -minZ;
            float toMaxZ = maxZ - z;
            float closest = fminf(fminf(toMinX, toMaxX), fminf(toMinZ, toMaxZ));

            if(closest == toMinX){
                x = minX;
            }else if(closest == toMaxX){
                x = maxX;
            }else if(closest == toMinZ){
                z = minZ;
            }else{
                z = maxZ;
            }
        }
    }

    gameCarema->camera.position.x = x;
    gameCarema->camera.position.z = z;
    gameCarema->camera.target.x += x - oldX;
    gameCarema->camera.target.z += z - oldZ;
}

int main(void){

    InitWindow( 1280, 720, "Run Away");
    InitAudioDevice();
    loadTerrainTexture();
    loadTerrainShader();
    initMenu();
    initDarkness();
    //DisableCursor();
    SetExitKey(KEY_NULL);
    SetTargetFPS(60);

    Door door = {0};

    static Floor houseFloor;
    Model house = LoadModel("assets/3Dmodels/free_abandoned_apartment.glb");
    Vector3 housePosition = {0.0f, 0.0f, -15.0f};
    Vector3 weaponPickUpPosition = {0};
    bool houseVisible = false;
    bool houseWorldActive = false;

    // printf("Mes: %d\n", house.meshCount);
    // printf("mate: %d\n", house.materialCount);

    // int textureM = 0;
    // for(int i = 0; i< house.materialCount; i++){
    //     if(house.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture.id > 0){
    //         textureM++;
    //     }
    //     //printf("material %d Texture id: %u cor: r=%d cor: g=%d cor: b=%d cor: a=%d\n", i, map.texture.id, map.color.r, map.color.g, map.color.b, map.color.a);
    // }

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

            if(!houseVisible){                
                updateWorld(camera.camera.position);
                updateTerrainShader(camera.camera.position, camera.camera.target);
            }
            BeginDrawing();
                ClearBackground((Color){10, 14, 17, 255});
            
                initCamera(&camera);
                    if(!houseWorldActive){
                        drawWorld();
                        drawDoor(&door);
                    }
                    if(houseVisible){
                        DrawModel(house, housePosition, 1.0f, WHITE);
                    }
                    weaponPickUpPosition = (Vector3){housePosition.x, housePosition.y  + 0.2f, housePosition.z};
                    if(houseWorldActive){
                        drawFloor(houseFloor);
                    }
                    if(houseWorldActive && !weapon.hasWeapon){
                        drawWeaponPickUp(&weapon, weaponPickUpPosition, camera.camera);
                    }
                finishCamera();

                if(houseWorldActive){
                    drawDarkness();
                }
                
                drawCutscene(&cutscene);
            EndDrawing();
            if(finished){
                gameState = GAME_STATE_PLAIYING;
            }

            continue;
        }

        updateCamera(&camera);
        if(houseWorldActive){
            keepPlayerOutWalls(&camera);
        }

        if(houseWorldActive && !weapon.hasWeapon){
            float distance = Vector3Distance(camera.camera.position, weaponPickUpPosition);
            
            if(distance <= 2.0f && IsKeyPressed(KEY_F)){
                pickUpWeapon(&weapon);
            }
        }
        if(!houseWorldActive){
            snapCameraToGround(&camera, 1.7f);
        }
        updateDimension();
        if(didDimensionJustChanged()){
            resetWorld();
            Vector3 spaw = (getCurrentDimension() == INFECTED_DIMENSION) ? (Vector3){0.0f, 1.7f, 0.0f} : (Vector3){0.0f, 1.7f, -26.0f};
            camera.camera.position = spaw;
            camera.camera.target = (Vector3){
                spaw.x, spaw.y, spaw.z + 1.0f
            };
        }
        if(!houseWorldActive){
            updateWorld(camera.camera.position);
            updateTerrainShader(camera.camera.position, camera.camera.target);
        }
            
        if(!houseWorldActive && updateDoor(&door, camera.camera.position)){
            //Vector3 direction = Vector3Subtract(camera.camera.target, camera.camera.position);
          
            //direction.y = 0.0f;
            // direction = Vector3Normalize(direction);

            housePosition = (Vector3){
               0.0f,0.0f,0.0f //camera.camera.position.x + direction.x * 12.0f, 0.0f, camera.camera.position.z + direction.z * 12.0f 
            };
            
            houseFloor = createFloor(housePosition.x, housePosition.y - 0.1f, housePosition.z, 70.0f, 70.0f, BLACK);

            houseVisible = true;
            houseWorldActive = true;

            camera.camera.position = (Vector3){
                -12.0f, 1.7f, -7.0f
            };
            camera.camera.target = (Vector3){
                -11.0f, 1.7f, -7.0f
            };

            startDoorCutscene(&cutscene, &camera);
            gameState = GAME_STATE_CUTSCENE;
        }
        updateWeapon(&weapon);
        updateWeaponAnimation(&weapon);

        bool dFire = updateWeaponFiring(&weapon);
        (void)dFire;

        BeginDrawing();
            ClearBackground((Color){10, 14, 17, 255});
            initCamera(&camera);
            if(!houseWorldActive){
                drawWorld();
                drawDoor(&door);
            }
            if(houseVisible){
                DrawModel(house, housePosition, 1.0f, WHITE);//(Color){150, 135, 115, 255});
            }
            if(houseWorldActive){
                drawFloor(houseFloor);
            }
                drawWeapon(&weapon, camera.camera);
            finishCamera();

            if(houseWorldActive && !weapon.hasWeapon){
                float distance = Vector3Distance(camera.camera.position, weaponPickUpPosition);
            
                if(distance <= 2.0f && IsKeyPressed(KEY_F)){
                    DrawText("[F] Get weapon", GetScreenWidth() / 2 - 100, GetScreenHeight() - 100, 25, RAYWHITE);
                    //pickUpWeapon(&weapon);
                }
            }

                if(houseWorldActive){
                    drawDarkness();
                }
                if(weapon.hasWeapon){
                    DrawText(TextFormat("%d / %d", weapon.magazineAmmo, weapon.reserveAmmo), GetScreenWidth() - 120, GetScreenHeight() - 26, 30, RAYWHITE);
                }
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
    unloadDarkness();
    unloadMenu();
    UnloadModel(house);
    unloadDoor(&door);
    CloseWindow();
    return 0;

}