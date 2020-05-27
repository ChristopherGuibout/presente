
#include <raylib.h>
#include <math.h>

#include "level.h"
#include "draw.h"
#include "state.h"

int main(int argc, char const *argv[]){

    // Initialization
    const int screen_width = 800;
    const int screen_height = 600;

    InitWindow(screen_width,screen_height,"Presente - the game");
    SetTargetFPS(60);

    // Initialize level and fill randomly
    level *lvl = level_new(50,40);
    level_fill_random(lvl,6);

    // Initialize state (and add enemies)
    state *sta = state_new();
    state_populate_random(lvl,sta,40);


    // Load textures
    Texture2D personajes = LoadTexture("./assets/charactersheet.png");


    // Animations variables

    float frameWidth = (float)(personajes.width/6);
    int maxFrames = (int)(personajes.width/(int)frameWidth);

    float timer = 0.0f;
    int frames= 0;


    // Main loop
    while(!WindowShouldClose()){

        // Update input depending if keys are pressed or not
        sta->button_state[0] = IsKeyDown(KEY_D);
        sta->button_state[1] = IsKeyDown(KEY_W);
        sta->button_state[2] = IsKeyDown(KEY_A);
        sta->button_state[3] = IsKeyDown(KEY_S);
        sta->button_state[4] = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
        // Compute the angle the player is looking at from the mouse's position relative to the screen's center
        float mouse_y = GetMouseY()-GetScreenHeight()/2;
        float mouse_x = GetMouseX()-GetScreenWidth()/2;
        sta->aim_angle = atan2(-mouse_y,mouse_x);

        // Check direction character is facing
        float dir_x = 0;
        float dir_y = 0;

        dir_x += sta->button_state[0];
        dir_x -= sta->button_state[2];
        dir_y += sta->button_state[1];
        dir_y -= sta->button_state[3];

        Vector2 direccion = {dir_x,dir_y};


        // Update the state
        state_update(lvl,sta);

        // Drawing
        BeginDrawing();

            ClearBackground(LIME);

            timer += GetFrameTime();

            if (timer >= 0.1f){
              timer = 0.0f;
              frames += 1;
            }

            frames = frames % maxFrames;

            draw_state(lvl, sta, timer, direccion, frames, frameWidth, personajes);

            DrawText("quirvi",190,200,20,PINK);

        EndDrawing();

    }

    // Closer window
    CloseWindow();

    // Free memory
    state_free(sta);
    level_free(lvl);

    return 0;
}
