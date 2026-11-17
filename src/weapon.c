#include "../include/weapon.h"
#include "../include/raymath.h"

Weapon createWeapon(void){
    Weapon weapon = {0};

    weapon.model = LoadModel("assets/3Dmodels/fps_animations_vsk.glb");

    TraceLog(LOG_INFO, "marma: meshes=%d materials=%d", weapon.model.meshCount, weapon.model.materials);

    weapon.offsetFromCamera = (Vector3){
        0.0f, 0.0f, 0.0f
    };
    weapon.correctionAngles = (Vector3){
        0.0f, 0.0f, 0.0f
    };
    weapon.scale = 1.0f;

    return weapon;
}
