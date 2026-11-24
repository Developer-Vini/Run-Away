#ifndef WEAPON_H
#define WEAPON_H

#include "../include/raylib.h"
#include <stdbool.h>

typedef struct {
    Model model;
    Vector3 offsetFromCamera;
    Vector3 correctionAngles;
    float scale;
    ModelAnimation *animations;
    int animationsCount;
    int currentAnimation;
    int armsMeshI;
    float currentFrame;

    Shader shader;
    int vPositionLocation;

    bool hasWeapon;

    int magazineAmmo;
    int reserveAmmo;
    float fireColdown;

    Sound shotSound;
    Sound emptySound;
    Sound rechargeSound;
} Weapon;

Weapon createWeapon(void);
void updateWeapon(Weapon *weapon);
void drawWeapon(Weapon *weapon, Camera3D camera);
void unloadWeapon(Weapon *weapon);
void updateWeaponAnimation(Weapon *weapon);
void pickUpWeapon(Weapon *weapon);
bool updateWeaponFiring(Weapon *weapon);

#endif