#ifndef DRAW_H
#define DRAW_H

#include <raylib.h>
#include "level.h"
#include "state.h"




// Draws the cells of the level in the screen
void draw_level(const level *lvl);

// Draws the whole state and the level in the screen
void draw_state(const level *lvl, const state *sta, float tim, Vector2 direc, int frame, float framethicc, const Texture2D persona);

#endif
