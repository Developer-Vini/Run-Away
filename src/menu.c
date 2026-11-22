#include "../include/menu.h"
#include "../include/raylib.h"

// #define BUTTON_WIDTH 300.0f
// #define BUTTON_HEIGHT 60.0f
// #define BUTTON_SPACING 20.0f
#define BUTTON_COUNT 3

static Texture2D menuBackground;
static bool menuLoaded = false;

static const char *buttonLabels[BUTTON_COUNT] = { "Play","Settings", "Exit" };

static Rectangle getButton(int index){
    int W = GetScreenWidth();
    int H = GetScreenHeight();
    
    //float totalH = BUTTON_COUNT * BUTTON_HEIGHT + (BUTTON_COUNT - 1) * BUTTON_SPACING;
    
    float x = W * 0.09f;
    float y = H * 0.48f + index * 65.f;

    int fontSize = 28;

    return (Rectangle){
        x, y, (float)MeasureText(buttonLabels[index], fontSize) + 25.0f, 42.0f
    };
}

void initMenu(void){
    menuBackground = LoadTexture("assets/images/background.png");
    menuLoaded = IsTextureValid(menuBackground);
}

void unloadMenu(void){
    if(menuLoaded){
        UnloadTexture(menuBackground);
        menuLoaded = false;
    }
}

MenuAction updateMenu(void){
    Vector2 mouse = GetMousePosition();

    if(IsKeyPressed(KEY_ENTER)){
        return MENU_ACTION_PLAY;
    }
    if(!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){    
        return MENU_ACTION_NONE;
    }
    if(CheckCollisionPointRec(mouse, getButton(0))){
        return MENU_ACTION_PLAY;
    }
    if(CheckCollisionPointRec(mouse, getButton(1))){
        return MENU_ACTION_QUIT;
    }

    return MENU_ACTION_NONE;
}
void drawMenu(void){
    
    int W = GetScreenWidth();
    int H = GetScreenHeight();
    
    ClearBackground(BLACK);

    if(menuLoaded){
        float imageR = (float)menuBackground.width / menuBackground.height;
        float scRatio = (float)W / H;

        Rectangle source = {
            0,0, (float)menuBackground.width, (float)menuBackground.height
        };

        if(imageR > scRatio){
            source.width = menuBackground.height * scRatio;
            source.x = (menuBackground.width - source.width) / 2.0f;
        }else{
            source.height = menuBackground.width / scRatio;
            source.y = (menuBackground.height - source.height) / 2.0f;
        }
        DrawTexturePro(menuBackground, source, (Rectangle){0, 0, (float)W, (float)H}, (Vector2){0, 0}, 0.0f, WHITE);
    }

    const char *title = "Run Away";
    int titleSize = 64;

    float tX = W * 0.09f;
    float tY = H * 0.29f; 

    DrawText(title, tX, tY, titleSize, WHITE);

    Vector2 mouse = GetMousePosition();

    for(int i = 0; i < BUTTON_COUNT; i++){
        Rectangle button = getButton(i);

        bool isHovered = CheckCollisionPointRec(mouse, button);

        Color fill = isHovered ? (Color){90, 20, 20, 255} : WHITE;

        int textSize = 32;
        DrawText(buttonLabels[i], (int)button.x, (int)button.y, textSize, fill);
    }
}