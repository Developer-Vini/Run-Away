#ifndef WEAPON_H
#define WEAPON_H

#include "../include/raylib.h"

typedef struct {
    Model model;
    Vector3 offsetFromCamera;
    Vector3 correctionAngles;
    float scale;
} Weapon;

Weapon createWeapon(void);
void updateWeapon(Weapon *weapon);
void drawWeapon(Weapon *weapon, Camera3D camera);
void unloadWeapon(Weapon *weapon);

#endif