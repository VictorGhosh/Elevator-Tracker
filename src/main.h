// main.h

#ifndef MAIN_H
#define MAIN_H


class World;
extern World *world;

class StrokeFont;
extern StrokeFont *strokeFont;

typedef enum { UP, DOWN } KeyState;
extern KeyState upKey, downKey, leftKey, rightKey, spaceBar;

extern int screenWidth, screenHeight;

#endif
