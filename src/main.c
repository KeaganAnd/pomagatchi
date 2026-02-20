/*******************************************************************************************

Desktop Critter

Omar, Keagan
02/18/2026

********************************************************************************************/

#include "../external/raylib.h"
#include "platform.h"
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

    Texture2D clockTexture = LoadTextureFromImage(clock); // Creates texture from img
    SetTextureFilter(clockTexture, TEXTURE_FILTER_POINT); // Disables filtering to keep scaled pixel art sharp

    Font pixelFont = LoadFont("../fonts/m6x11.ttf");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update

        // Draw
        

        BeginDrawing();
            const int screenWidth = GetScreenWidth();
            const int screenHeight = GetScreenHeight();

            Vector2 clockPostion = (Vector2){screenWidth/2 - (clockTexture.width * uiScale)/2,
            screenHeight - (clockTexture.height * uiScale)}; // The position where the clock texture will be drawn, 
            // stored so you can draw other elements based on it pos
            Vector2 textSize = MeasureTextEx(pixelFont, "Test Font", 40.0f, 5.0f); 
            Vector2 clockTextPosition = (Vector2){clockPostion.x + ((63*uiScale)-textSize.x/2), clockPostion.y + ((24*uiScale)-textSize.y/2)}; // The size from the top of the texture to the
        // bottom of the "screen" is 48 pixels and from left to edge is 126, 24 is half way down 63 is half across
            ClearBackground(BLANK);

            DrawTextureEx(clockTexture, clockPostion, 0.0f, uiScale, WHITE);

            DrawTextEx(pixelFont, "Test Font", clockTextPosition, 40.0f, 5.0f, WHITE);

        EndDrawing();
    }

    // De-Initialization || Need to clean up all loaded textures, fonts, audios, etc
    UnloadTexture(clockTexture);
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
