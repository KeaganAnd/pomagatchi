#include "flipBook.h"
#include "raylib.h"
#include <stdlib.h>

flipBook *createFlipBook(Texture2D texture, u_int8_t length, Vector2 spriteSize,
                         Vector2 start, u_int8_t frameRate) {
  flipBook *flipResult = malloc(sizeof(flipBook));
  flipResult->texture = texture;
  flipResult->frame = 0;
  flipResult->flipLength = length;
  flipResult->spriteSize = spriteSize;
  flipResult->startingFrame = start;
  flipResult->frameRate = frameRate;
  flipResult->frameTime = 1.0f / frameRate;
  flipResult->timer = 0.0f;

  return (flipResult);
}

void drawFlipBook(flipBook *flip, Vector2 position, float scale) {

  flip->timer += GetFrameTime();
  if (flip->timer >= flip->frameTime) {
    flip->frame++;
    if (flip->frame >= flip->flipLength) {
      flip->frame = 0;
    }
    flip->timer -= flip->frameTime;
  }

  Rectangle source = {(flip->startingFrame.x * flip->spriteSize.x) +
                          (flip->spriteSize.x * flip->frame),

                      (flip->startingFrame.y * flip->spriteSize.y),
                      flip->spriteSize.x, flip->spriteSize.y};

  Rectangle dest = {position.x, position.y, flip->spriteSize.x * scale,
                    flip->spriteSize.y * scale};

  Vector2 origin = {0, 0};

  DrawTexturePro(flip->texture, source, dest, origin, 0.0f, WHITE);
}
