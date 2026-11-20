#include "../include/camera.h"
#include "../include/chunk.h"

void createCamera(GameCamera *GC, Vector3 position, Vector3 target){
    int fovy = 45.0f;
    int projection = CAMERA_PERSPECTIVE;
    int mode = CAMERA_FIRST_PERSON;

    GC->camera.position = position;
    GC->camera.target = target;
    GC->camera.up = (Vector3){0.0f, 1.0f, 0.0f};

    GC->camera.fovy = fovy;
    GC->camera.projection = projection;


    GC->cameraMode = mode;

}

void updateCamera(GameCamera *UCG){
    // Vector3 befPos = UCG->camera.position;
    // Vector3 befTar = UCG->camera.target;

    UpdateCamera(&UCG->camera, UCG->cameraMode);

    // if(IsKeyDown(KEY_E)){
    //     UCG->camera.position.y = befPos.y;
    //     UCG->camera.target.y = befTar.y;
    // }
}

void initCamera(GameCamera *IGC){
    BeginMode3D(IGC->camera);
}

void finishCamera(void){
    EndMode3D();
}

void snapCameraToGround(GameCamera *GC, float eyeH){
    float groundH = getTerrainH(GC->camera.position.x, GC->camera.position.z);
    float newY = groundH + eyeH;

    float diference = newY - GC->camera.position.y;
    GC->camera.position.y += diference;
    GC->camera.target.y += diference;
}

// void testERotate(){
//         float deltaTime = GetFrameTime();

//         Vector3 foward = Vector3Subtract(UCG->camera.target, UCG->camera.position);
    
//         foward.y = 0.0f;
//         foward = Vector3Normalize(foward);
    
//         Vector3 right = Vector3Normalize(Vector3CrossProduct(foward, UCG->camera.up));
//         Vector3 mov = {0};
    
//         if(IsKeyDown(KEY_W)){
//             mov = Vector3Add(mov, foward);
//         }
//         if(IsKeyDown(KEY_S)){
//             mov = Vector3Subtract(mov, foward);
//         }
//         if(IsKeyDown(KEY_D)){
//             mov = Vector3Add(mov, right);
//         }
//         if(IsKeyDown(KEY_A)){
//             mov = Vector3Subtract(mov, right);
//         }
    
//         if(Vector3Length(mov) > 0.0f){
//             mov = Vector3Normalize(mov);
//             mov = Vector3Scale(mov, UCG->moviSpeed * deltaTime);
        
//             UCG->camera.position = Vector3Add(UCG->camera.position, mov);
//             UCG->camera.target = Vector3Add(UCG->camera.target, mov);
//         }
    
//         Vector2 mouseDelta = GetMouseDelta();
    
//         Vector3 view = Vector3Subtract(UCG->camera.target, UCG->camera.position);
    
//         float yaw = atan2f(view.x, view.z);
//         float pitch = -asinf(view.y / Vector3Length(view));
    
//         yaw -= mouseDelta.x * UCG->mouseSesi;
//         pitch -= mouseDelta.y * UCG->mouseSesi;
    
//         if(pitch > 1.5f){
//             pitch  = 1.5f;
//         }
//         if(pitch < -1.5f){
//             pitch = -1.5f;
//         }
    
//         Vector3 direction = {sinf(yaw) * cosf(pitch), -sinf(pitch), cosf(yaw) * cosf(pitch)};
    
//         UCG->camera.target = Vector3Add(UCG->camera.position, direction);
//         UpdateCamera(&UCG->camera, UCG->cameraMode);
// }