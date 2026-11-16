#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

typedef struct {
    int chunkX;
    int chunkZ;
    float heights[CHUNK_SIZE][CHUNK_SIZE]; 
    
} Chunk;

Chunk createChunk(int chunkX, int chunkZ);
void drawChunk(const Chunk *chunk);
void generateChunkTerrain(Chunk *chunk);
float getTerrainH(float worldX, float worldZ);

#endif