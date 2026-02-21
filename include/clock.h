#pragma once

#include <stdbool.h>

typedef struct PomodoroTimer
{
    float duration;     // Total duration in seconds
    float elapsed;      // Elapsed time
    bool running;
} PomodoroTimer;

// Functions
void Timer_Init(PomodoroTimer *t, float duration);
void Timer_Start(PomodoroTimer *t);
void Timer_Pause(PomodoroTimer *t);
void Timer_Reset(PomodoroTimer *t);
void Timer_Update(PomodoroTimer *t, float dt);
float Timer_GetRemaining(const PomodoroTimer *t);
bool Timer_IsFinished(const PomodoroTimer *t);
