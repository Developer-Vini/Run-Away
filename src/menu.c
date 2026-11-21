#include "../include/menu.h"
#include "../include/raylib.h"

// #define BUTTON_WIDTH 300.0f
// #define BUTTON_HEIGHT 60.0f
// #define BUTTON_SPACING 20.0f
#define BUTTON_COUNT 2

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

MenuAction updateMenu(void){
    if(IsKeyPressed(KEY_ENTER)) return MENU_ACTION_PLAY;

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        Vector2 mouse = GetMousePosition();
        if(CheckCollisionPointRec(mouse, getButton(0))){
            return MENU_ACTION_PLAY;
        }
        if(CheckCollisionPointRec(mouse, getButton(1))){
            return MENU_ACTION_QUIT;
        }

        return MENU_ACTION_NONE;
    }
}
void drawMenu(void){
    //ClearBackground((Color){10, 14, 17, 255});

    const char *title = "Run Away";
    int titleSize = 64;
    DrawText(title, (GetScreenWidth() - MeasureText(title, titleSize)) / 2, GetScreenHeight() / 4, titleSize, RAYWHITE);

    Vector2 mouse = GetMousePosition();

    for(int i = 0; i < BUTTON_COUNT; i++){
        Rectangle button = getButton(i);

        bool isHovered = CheckCollisionPointRec(mouse, button);

        Color fill = isHovered ? (Color){90, 20, 20, 255} : (Color){35, 38, 42, 255};
        DrawRectangleRec(button, fill);
        DrawRectangleLinesEx(button, 2.0f, GRAY);
        
        int textSize = 30;
        DrawText(buttonLabels[i], (int)(button.x + (BUTTON_WIDTH - MeasureText(buttonLabels[i], textSize)) / 2), (int)(button.y + (BUTTON_HEIGHT - textSize) / 2), textSize, RAYWHITE);
    }
}