#include "../include/chunk.h"
#include "../include/raylib.h"
#include <math.h>
#include "../include/raymath.h"

static void addTriangle(Mesh *mesh, int *vertexIndex, Vector3 a, Vector3 b, Vector3 c){
    Vector3 normal = Vector3Normalize(Vector3CrossProduct(Vector3Subtract(b, a), Vector3Subtract(c, a)));


    Vector3 lightDirection = Vector3Normalize((Vector3){0.5f, 1.0f, 0.3f});
    float light = Vector3DotProduct(normal, lightDirection);

    if(light < 0.0f){
        light = 0.0f;
    }

    float brig = 0.45f + 0.65f * light;

    Vector3 corners[3] = {
        a, b, c
    };

    for (int i = 0; i < 3; i++){
        int vertex = *vertexIndex;
        mesh->vertices[vertex * 3 + 0] = corners[i].x;
        mesh->vertices[vertex * 3 + 1] = corners[i].y;
        mesh->vertices[vertex * 3 + 2] = corners[i].z;
    
        mesh->normals[vertex * 3 + 0] = normal.x;
        mesh->normals[vertex * 3 + 1] = normal.y;
        mesh->normals[vertex * 3 + 2] = normal.z;
    
        mesh->colors[vertex * 4 + 0] = (unsigned char)(60 * brig);
        mesh->colors[vertex * 4 + 1] = (unsigned char)(160 * brig);
        mesh->colors[vertex * 4 + 2] = (unsigned char)(70 * brig);
        mesh->colors[vertex * 4 + 3] = 255;

        (*vertexIndex)++;
    }

}



Chunk createChunk(int chunkX, int chunkZ){
    Chunk chunk = {0};

    chunk.chunkX = chunkX;
    chunk.chunkZ = chunkZ;

    generateChunkTerrain(&chunk);

    return chunk;
}

void drawChunk(const Chunk *chunk){
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            float worldX = (float)(chunk->chunkX *  CHUNK_SIZE + x);
            float worldZ = (float)(chunk->chunkZ *  CHUNK_SIZE + z);

            Vector3 pointA = {
                worldX, chunk->heights[x][z], worldZ
            };
            Vector3 pointB = {
                worldX + 1, getTerrainH(worldX + 1, worldZ), worldZ
            };
            Vector3 pointC = {
                worldX, getTerrainH(worldX, worldZ + 1), worldZ + 1
            };
            Vector3 pointD = {
                worldX + 1, getTerrainH(worldX + 1, worldZ + 1), worldZ + 1
            };

            DrawTriangle3D(pointA, pointC, pointB, DARKGREEN);
            DrawTriangle3D(pointB, pointC, pointD, DARKGREEN);
            DrawLine3D(pointA, pointB, DARKPURPLE);
            //DrawLine3D(pointA, pointC, DARKGRAY);
            
            //DrawSphere(position, 0.15f, DARKGREEN);
        }
    }
}

void generateChunkTerrain(Chunk *chunk){
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            float worldX = (float)(chunk->chunkX *  CHUNK_SIZE + x);
            float worldZ = (float)(chunk->chunkZ *  CHUNK_SIZE + z);

            chunk->heights[x][z] = getTerrainH(worldX, worldZ);

            //DrawSphere(position, 0.15f, DARKGREEN);
        }
    }
}

float getTerrainH(float worldX, float worldZ){
    float height = 0.0f;
    height += sinf(worldX * 0.05f) * cosf(worldZ * 0.05f) * 8.0f;
    height += sinf(worldX * 0.15f + worldZ * 0.1f) * 2.0f;
    height += cosf(worldZ * 0.4f  + worldX * 0.3f) * 0.5f;
    return height;
}

int floorDivide(int value, int divisor){
    int quotient = value / divisor;

    if((value % divisor !=0) && ((value < 0) != (divisor < 0))){
        quotient--;
    }

    return quotient;
}

int positiveModule(int value, int divisor){
    int reminder = value % divisor;

    return reminder < 0 ? reminder + divisor : reminder;
}