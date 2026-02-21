/*******************************************************************************************

Desktop Critter

Omar, Keagan
02/18/2026

********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include "platform.h"
#include "clock.h"
#include "buttons.h"
#include <stdio.h>
// Constants

#define uiScale 4.0f // Scale for the ui since pixel art is small resolutions

// Program main entry point

int main(void)
{
    // Initialization

    SetConfigFlags(FLAG_WINDOW_TRANSPARENT | FLAG_WINDOW_UNDECORATED); // Configures window to be transparent
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Pomagatchi");

    Platform_SetDesktopMode();

    SetWindowPosition(0,0);
    SetTargetFPS(60);
    
    // Load test cat image
    Image clock = LoadImage("../imgs/clock.png"); // Loads the fish image into memory
    Image button = LoadImage("../imgs/button.png");

    Texture2D clockTexture = LoadTextureFromImage(clock); // Creates texture from img
    Texture2D buttonTexture = LoadTextureFromImage(button);

    SetTextureFilter(clockTexture, TEXTURE_FILTER_POINT); // Disables filtering to keep scaled pixel art sharp

    Font pixelFont = LoadFont("../fonts/m6x11.ttf");
    
    PomodoroTimer timer;
    Timer_Init(&timer, 25 * 60); // 25 minutes
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        float dt = GetFrameTime();
        Timer_Update(&timer, dt);
        float remaining = Timer_GetRemaining(&timer);
        int minutes = (int)(remaining / 60);
        int seconds = (int)(remaining) % 60;
        char buffer[16];
        snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
        // Draw
        

        BeginDrawing();
            const int screenWidth = GetScreenWidth();
            const int screenHeight = GetScreenHeight();

            Vector2 clockPostion = (Vector2){screenWidth/2 - (clockTexture.width * uiScale)/2,
            screenHeight - (clockTexture.height * uiScale)}; // The position where the clock texture will be drawn, 
            // stored so you can draw other elements based on it pos

            Vector2 buttonPosition = (Vector2){(19 * uiScale) + clockPostion.x,clockPostion.y + (clockTexture.height * uiScale) - (4 * uiScale) - (buttonTexture.height * uiScale)};
            Vector2 button2Positon = Vector2Add(buttonPosition, (Vector2){(20 + buttonTexture.width) * uiScale ,0});
            Vector2 button3Positon = Vector2Add(buttonPosition, (Vector2){(41 + (2 * buttonTexture.width)) * uiScale , 0});
        

            Vector2 textSize = MeasureTextEx(pixelFont, buffer, 40.0f, 5.0f); 
            Vector2 clockTextPosition = (Vector2){clockPostion.x + ((63*uiScale)-textSize.x/2), clockPostion.y + ((24*uiScale)-textSize.y/2)}; // The size from the top of the texture to the
        // bottom of the "screen" is 48 pixels and from left to edge is 126, 24 is half way down 63 is half across
            ClearBackground(BLANK);

            DrawTextureEx(clockTexture, clockPostion, 0.0f, uiScale, WHITE);
            
            
            DrawTextEx(pixelFont, buffer, clockTextPosition, 40.0f, 5.0f, WHITE);

            Vector2 mousePos = GetMousePosition();

            Color button1Color = IsMouseOverEllipse(mousePos, buttonPosition, (Vector2){buttonTexture.width,buttonTexture.height}, uiScale) ? LIGHTGRAY : WHITE;
            Color button2Color = IsMouseOverEllipse(mousePos, button2Positon, (Vector2){buttonTexture.width,buttonTexture.height}, uiScale) ? LIGHTGRAY : WHITE;
            Color button3Color = IsMouseOverEllipse(mousePos, button3Positon, (Vector2){buttonTexture.width,buttonTexture.height}, uiScale) ? LIGHTGRAY : WHITE;
            DrawTextureEx(buttonTexture, buttonPosition, 0.0f, uiScale, button1Color);
            DrawTextureEx(buttonTexture, button2Positon, 0.0f, uiScale, button2Color);
            DrawTextureEx(buttonTexture, button3Positon, 0.0f, uiScale, button3Color);

        EndDrawing();
    }

    // De-Initialization || Need to clean up all loaded textures, fonts, audios, etc
    UnloadTexture(clockTexture);
    UnloadFont(pixelFont);
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
