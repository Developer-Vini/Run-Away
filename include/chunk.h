#ifndef CHUNK_H
#define CHUNK_H

#define CHUNK_SIZE 16

typedef struct {
    int chunkX;
    int chunkZ;
    float heights[CHUNK_SIZE][CHUNK_SIZE]; 
    
} Chunk;


#endif