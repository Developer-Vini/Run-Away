#include "../include/raylib.h"
#include "../include/floor.h"
#include "../include/camera.h"
#include "../include/chunk.h"

#include <math.h>
#include <stdbool.h>

#define VIEW_RADIUS 4
#define GRID_SIZE (VIEW_RADIUS * 2 + 1)

static Chunk loadedChuncks[GRID_SIZE][GRID_SIZE];
static bool isLoaded[GRID_SIZE][GRID_SIZE];

static void updateChunks(Vector3 playerPosition){
    int playerChunkX = floorDivide((int)floorf(playerPosition.x), CHUNK_SIZE);
    int playerChunkZ = floorDivide((int)floorf(playerPosition.z), CHUNK_SIZE);

    for(int offsetX = -VIEW_RADIUS; offsetX <= VIEW_RADIUS; offsetX++){
        for(int offsetZ = -VIEW_RADIUS; offsetZ <= VIEW_RADIUS; offsetZ++){
            int chunkX = playerChunkX + offsetX;
            int chunkZ = playerChunkZ + offsetZ;

            int slotX = positiveModule(chunkX, GRID_SIZE);
            int slotZ = positiveModule(chunkZ, GRID_SIZE);

            Chunk *slot = &loadedChuncks[slotX][slotZ];
            bool isWrongChun = slot->chunkX != chunkX || slot->chunkZ != chunkZ;

            if(!isLoaded[slotX][slotZ] || isWrongChun){
                *slot = createChunk(chunkX, chunkZ);
                isLoaded[slotX][slotZ] = true;
            }
        }
    }
}

static void drawWorld(void){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(isLoaded[i][j]){
                drawChunk(&loadedChuncks[i][j]);
            }
        }
    }
}
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
        updateChunks(camera.camera.position);
        BeginDrawing();
            ClearBackground(BLACK);
            initCamera(&camera);
                drawFloor(mainFloor);
                drawWorld();
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