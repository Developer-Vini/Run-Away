#include "../include/chunk.h"
#include "../include/raylib.h"

Chunk createChunk(int chunkX, int chunkZ){
    Chunk chunk = {0};

    chunk.chunkX = chunkX;
    chunk.chunkZ = chunkZ;

    return chunk;
}

void drawChunk(const Chunk *chunk){
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            Vector3 position = {
                (float)(chunk->chunkX *  CHUNK_SIZE + x),
                chunk->heights[x][z],
                (float)(chunk->chunkZ * CHUNK_SIZE + z)
            };
            //DrawSphere(position, 0.15f, DARKGREEN);
        }
    }
}