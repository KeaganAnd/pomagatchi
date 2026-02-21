#include "clock.h"
#include <stdbool.h>

void Timer_Init(PomodoroTimer *t, float duration)
{
    t->duration = duration;
    t->elapsed = 0.0f;
    t->running = false;
}

void Timer_Start(PomodoroTimer *t) { t->running = true; }
void Timer_Pause(PomodoroTimer *t) { t->running = false; }
void Timer_Reset(PomodoroTimer *t) { t->elapsed = 0.0f; t->running = false; }

void Timer_Update(PomodoroTimer *t, float dt)
{
    if (t->running)
    {
        t->elapsed += dt;
        if (t->elapsed > t->duration)
            t->elapsed = t->duration;
    }
}

float Timer_GetRemaining(const PomodoroTimer *t)
{
    return t->duration - t->elapsed;
}

bool Timer_IsFinished(const PomodoroTimer *t)
{
    return t->elapsed >= t->duration;
}
