/*******************************************************************************************

Desktop Critter

Omar, Keagan
02/18/2026

********************************************************************************************/

#include "buttons.h"
#include "clock.h"
#include "flipBook.h"
#include "platform.h"
#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdlib.h>
// Constants

#define uiScale 4.0f // Scale for the ui since pixel art is small resolutions
#define pomoTime                                                               \
  0.3f // Time for work time, short break, and long break | Default 25.0f
#define shortBreakTime 0.1f  // Default 5.0f
#define longBreakTime 0.2f   // Default 15.0f
#define longBreakThreshold 2 // Default 2

typedef enum { SHORT_BREAK, LONG_BREAK, WORKING } Phase;
Phase currentPhase = WORKING;

// Program main entry point

int main(void) {
  // Initialization

  SetConfigFlags(
      FLAG_WINDOW_TRANSPARENT |
      FLAG_WINDOW_UNDECORATED); // Configures window to be transparent
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Pomagatchi");
  InitAudioDevice();

  Platform_SetDesktopMode();

  SetWindowPosition(0, 0);
  SetTargetFPS(60);

  // Load images and textures
  Image clock = LoadImage("../imgs/clock.png");
  Image button = LoadImage("../imgs/button.png");
  Image catSpriteImage = LoadImage("../sprites/OrangeCat.png");

  Texture2D clockTexture =
      LoadTextureFromImage(clock); // Creates texture from img
  Texture2D buttonTexture = LoadTextureFromImage(button);
  Texture2D catSprites = LoadTextureFromImage(catSpriteImage);

  SetTextureFilter(clockTexture,
                   TEXTURE_FILTER_POINT); // Disables filtering to keep scaled
                                          // pixel art sharp

  // Fonts
  Font pixelFont = LoadFont("../fonts/m6x11.ttf");

  // Sounds
  Sound pomoSwitch = LoadSound("../sounds/ding.wav");

  PomodoroTimer timer;
  Timer_Init(&timer, pomoTime * 60); // 25 minutes
  u_int8_t pomoCount = 0; // How many times a pomo cycle has been completed to
                          // see when a short break should happen
  Vector2 spriteSize = {32.0f, 32.0f}; // Size of the sprites
  Vector2 start = {
      0.0f, 2.0f}; // Coordinates where the first frame is starts at (0,0)
  flipBook *catLongAni = createFlipBook(catSprites, 4, spriteSize, start, 2);
  flipBook *catShortAni =
      createFlipBook(catSprites, 12, spriteSize, (Vector2){0.0f, 6.0f}, 2);
  flipBook *catActiveAni =
      createFlipBook(catSprites, 12, spriteSize, (Vector2){0.0f, 9.0f}, 2);
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
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

    // printf("Laps: %d\n", pomoCount);

    if (timer.elapsed == timer.duration) {
      if (timer.duration == (pomoTime * 60)) {
        pomoCount += 1;
        if (pomoCount == longBreakThreshold) {
          currentPhase = LONG_BREAK;
          printf("Long break\n");
          timer.duration = (longBreakTime * 60);
        } else {
          printf("Short break\n");
          currentPhase = SHORT_BREAK;
          timer.duration = (shortBreakTime * 60);
        }
        Timer_Reset(&timer);
        Timer_Start(&timer);
        PlaySound(pomoSwitch);
      } else if (timer.duration == (shortBreakTime * 60)) {
        currentPhase = WORKING;
        printf("Active Phase\n");
        timer.duration = (pomoTime * 60);
        Timer_Reset(&timer);
        Timer_Start(&timer);
        PlaySound(pomoSwitch);
      }
    }

    Vector2 clockPostion = (Vector2){
        screenWidth / 2 - (clockTexture.width * uiScale) / 2,
        screenHeight -
            (clockTexture.height *
             uiScale)}; // The position where the clock texture will be drawn,
    // stored so you can draw other elements based on it pos

    Vector2 buttonPosition =
        (Vector2){(19 * uiScale) + clockPostion.x,
                  clockPostion.y + (clockTexture.height * uiScale) -
                      (4 * uiScale) - (buttonTexture.height * uiScale)};
    Vector2 button2Positon = Vector2Add(
        buttonPosition, (Vector2){(20 + buttonTexture.width) * uiScale, 0});
    Vector2 button3Positon =
        Vector2Add(buttonPosition,
                   (Vector2){(41 + (2 * buttonTexture.width)) * uiScale, 0});

    Vector2 textSize = MeasureTextEx(pixelFont, buffer, 40.0f, 5.0f);
    Vector2 clockTextPosition = (Vector2){
        clockPostion.x + ((63 * uiScale) - textSize.x / 2),
        clockPostion.y +
            ((24 * uiScale) -
             textSize.y / 2)}; // The size from the top of the texture to the
    // bottom of the "screen" is 48 pixels and from left to edge is 126, 24 is
    // half way down 63 is half across
    ClearBackground(BLANK);

    DrawTextureEx(clockTexture, clockPostion, 0.0f, uiScale, WHITE);

    DrawTextEx(pixelFont, buffer, clockTextPosition, 40.0f, 5.0f, WHITE);

    Vector2 mousePos = GetMousePosition();
    // Button colors
    Color button1Color = WHITE;
    Color button2Color = WHITE;
    Color button3Color = WHITE;

    // Check mouse over and clicks
    // Button 1 (Left) to button 3 (Right)
    if (IsMouseOverEllipse(mousePos, buttonPosition,
                           (Vector2){buttonTexture.width, buttonTexture.height},
                           uiScale)) {
      button1Color = LIGHTGRAY;
    }

    if (IsMouseOverEllipse(mousePos, button2Positon,
                           (Vector2){buttonTexture.width, buttonTexture.height},
                           uiScale)) {
      button2Color = LIGHTGRAY;
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (timer.running) {
          Timer_Pause(&timer);
        } else {
          Timer_Start(&timer);
        }
      }
    }

    if (IsMouseOverEllipse(mousePos, button3Positon,
                           (Vector2){buttonTexture.width, buttonTexture.height},
                           uiScale)) {
      button3Color = LIGHTGRAY;
    }
    DrawTextureEx(buttonTexture, buttonPosition, 0.0f, uiScale, button1Color);
    DrawTextureEx(buttonTexture, button2Positon, 0.0f, uiScale, button2Color);
    DrawTextureEx(buttonTexture, button3Positon, 0.0f, uiScale, button3Color);

    // Decide which cat to draw
    //
    printf("%d\n", currentPhase);
    if (currentPhase == LONG_BREAK) {
      drawFlipBook(catLongAni, clockPostion, uiScale);
    } else if (currentPhase == SHORT_BREAK) {
      drawFlipBook(catShortAni, clockPostion, uiScale);
    } else if (currentPhase == WORKING) {
      drawFlipBook(catActiveAni, clockPostion, uiScale);
    }

    EndDrawing();
  }

  // De-Initialization || Need to clean up all loaded textures, fonts, audios,
  // etc
  UnloadTexture(clockTexture);
  UnloadTexture(buttonTexture);
  UnloadTexture(catSprites);
  UnloadSound(pomoSwitch);
  UnloadFont(pixelFont);

  free(catLongAni);
  free(catShortAni);
  free(catActiveAni);

  CloseAudioDevice();

  CloseWindow(); // Close window and OpenGL context

  return 0;
}
