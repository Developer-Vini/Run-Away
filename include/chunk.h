#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

#include "../include/raylib.h"

typedef struct {
    int chunkX;
    int chunkZ;
    float heights[CHUNK_SIZE][CHUNK_SIZE]; 

    Model model;
    
} Chunk;

Chunk createChunk(int chunkX, int chunkZ);
void drawChunk(const Chunk *chunk);
void generateChunkTerrain(Chunk *chunk);
float getTerrainH(float worldX, float worldZ);
int floorDivide(int value, int divisor);
int positiveModule(int value, int divisor);

void unloadChunk(Chunk *chunk);
#endif