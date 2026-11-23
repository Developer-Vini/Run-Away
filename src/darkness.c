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
    darknessShader = LoadShader("assets/darkness.vs", "assets/darkness.fs");

    resolutionLoc = GetShaderLocation(darknessShader, "resolution");
    centerLoc = GetShaderLocation(darknessShader, "center");
    radiusLoc = GetShaderLocation(darknessShader, "radius");
    softnessLoc = GetShaderLocation(darknessShader, "softness");
    timeLoc = GetShaderLocation(darknessShader, "time");
}

void drawDarkness(void){
    Vector2 resolution = {(float)GetScreenWidth(), (float)GetScreenHeight()};

    Vector2 center = {0.5f, 0.5f};

    float radius = 0.3;
    float softness = 0.15;
    float time = (float)GetTime();

    SetShaderValue(darknessShader, resolutionLoc, &resolution, SHADER_UNIFORM_VEC2);
    SetShaderValue(darknessShader, centerLoc, &center, SHADER_UNIFORM_VEC2);
    SetShaderValue(darknessShader, radiusLoc, &radius, SHADER_UNIFORM_FLOAT);
    SetShaderValue(darknessShader, timeLoc, &time, SHADER_UNIFORM_FLOAT);
    SetShaderValue(darknessShader, softnessLoc, &softness, SHADER_UNIFORM_FLOAT);


    BeginShaderMode(darknessShader);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);
    EndShaderMode();
}

void unloadDarkness(void){
    UnloadShader(darknessShader);
}