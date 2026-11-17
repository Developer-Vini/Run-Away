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

static void buildChunckMesh(Chunk *chunk){
    float grid[CHUNK_SIZE + 1][CHUNK_SIZE + 1];

    for(int x = 0; x <= CHUNK_SIZE; x++){
        for(int z = 0; z <= CHUNK_SIZE; z++){
            grid[x][z] = getTerrainH((float)(chunk->chunkX * CHUNK_SIZE + x), (float)(chunk->chunkZ * CHUNK_SIZE + z));
        }
    }

    int quadCount = CHUNK_SIZE * CHUNK_SIZE;
    int vertexCount = quadCount * 6;

    Mesh mesh = {0};

    mesh.vertexCount = vertexCount;
    mesh.triangleCount = quadCount * 2;
    mesh.vertices = MemAlloc(vertexCount * 3 * sizeof(float));
    mesh.normals = MemAlloc(vertexCount * 3 * sizeof(float));
    mesh.texcoords = MemAlloc(vertexCount * 2 * sizeof(float));
    mesh.colors = MemAlloc(vertexCount * 4 * sizeof(unsigned char));

    int vertexIndex = 0;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            Vector3 pointA = {
               (float)x, grid[x][z], (float) z
            };
            Vector3 pointB = {
                (float)x + 1, grid[x + 1][z], (float)z
            };
            Vector3 pointC = {
                (float)x, grid[x][z + 1], (float)z + 1
            };
            Vector3 pointD = {
                (float)x + 1, grid[x + 1][z + 1], (float)z + 1
            };


            addTriangle(&mesh, &vertexIndex, pointA, pointC, pointB);
            addTriangle(&mesh, &vertexIndex, pointB, pointC, pointD);
        }
    }
    UploadMesh(&mesh, false);
    chunk->model = LoadModelFromMesh(mesh);
}


Chunk createChunk(int chunkX, int chunkZ){
    Chunk chunk = {0};

    chunk.chunkX = chunkX;
    chunk.chunkZ = chunkZ;

    generateChunkTerrain(&chunk);
    buildChunckMesh(&chunk);

    return chunk;
}

void drawChunk(const Chunk *chunk){
    Vector3 worldPosition = {(float)(chunk->chunkX * CHUNK_SIZE), 0.0f, (float)(chunk->chunkZ * CHUNK_SIZE)};
    DrawModel(chunk->model, worldPosition, 1.0f, WHITE);
}

void unloadChunk(Chunk *chunk){
    UnloadModel(chunk->model);
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
    float zone = sinf(worldX * 0.012f + 1.3f) * cosf(worldZ * 0.0009f + 0.7f);

    zone = (zone - 0.2f) / 0.6;
    if(zone < 0.0f){
        zone = 0.0f;
    }

    if(zone > 1.0f){
        zone = 1.0f;
    }

    zone = zone * zone * (3.0f - 2.0f * zone);

    float relief = 0.0f;

    relief += sinf(worldX * 0.05f) * cosf(worldZ * 0.05f) * 8.0f;
    relief += sinf(worldX * 0.15f + worldZ * 0.1f) * 2.0f;


    float detail = cosf(worldZ * 0.4f + worldX * 0.3f) * 0.2f;

    return relief * zone + detail;
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