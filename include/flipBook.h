#pragma once

#include <raylib.h>
#include <stdint.h>

typedef struct {
  Texture2D texture;
  Vector2 startingFrame;
  u_int8_t frameRate;
  u_int16_t frame;
  Vector2 spriteSize;
  u_int8_t flipLength;
  float frameTime;
  float timer;
} flipBook;

flipBook *createFlipBook(Texture2D texture, u_int8_t length, Vector2 spriteSize,
                         Vector2 start, u_int8_t frameRate);
void drawFlipBook(flipBook *flip, Vector2 position, float scale);
