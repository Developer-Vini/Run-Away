#ifndef PROP_H
#define PROP_H

#include "raylib.h"

typedef struct{
    bool exists;
    int modelIndex;
    Vector3 position;
    // float rotation;
    // float scale;
    /* data */
} Prop;

void loadProp(Shader fogShader);
void unloadProps(void);
Prop createProp(int chunkX, int chunkZ);
void drawProp(const Prop *prop);

#endif