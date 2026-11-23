#include "../include/darkness.h"
#include "../include/raylib.h"

#include "stdio.h"

static Shader darknessShader;

static int resolutionLoc;
static int centerLoc;
static int radiusLoc;
static int softnessLoc;
static int timeLoc;

void initDarkness(void){
    darknessShader = LoadShader(NULL, "assets/darkness.fs");

    resolutionLoc = GetShaderLocation(darknessShader, "resolution");
    centerLoc = GetShaderLocation(darknessShader, "center");
    radiusLoc = GetShaderLocation(darknessShader, "radius");
    softnessLoc = GetShaderLocation(darknessShader, "softness");
    timeLoc = GetShaderLocation(darknessShader, "time");
}