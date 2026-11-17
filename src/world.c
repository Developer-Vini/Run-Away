#include "world.h"
#include "chunk.h"
#include "floor.h"

#include <math.h>
#include <stdbool.h>


#define VIEW_RADIUS 4
#define GRID_SIZE (VIEW_RADIUS * 2 + 1)

static Chunk loadedChuncks[GRID_SIZE][GRID_SIZE];
static bool isLoaded[GRID_SIZE][GRID_SIZE];

void updateWorld(Vector3 playerPosition){
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


            //TraceLog(LOG_INFO, "criando chunk %d %d no slot %d %d", chunkX, chunkZ, slotX, slotZ);
            if(!isLoaded[slotX][slotZ] || isWrongChun){
                if(isLoaded[slotX][slotZ]){
                    unloadChunk(slot);
                }
                *slot = createChunk(chunkX, chunkZ);
                isLoaded[slotX][slotZ] = true;
            }
        }
    }
}

void drawWorld(void){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(isLoaded[i][j]){
                drawChunk(&loadedChuncks[i][j]);
            }
        }
    }
}

void unloadWorld(void){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            if(isLoaded[i][j]){
                unloadChunk(&loadedChuncks[i][j]);
            }
        }
    }
}