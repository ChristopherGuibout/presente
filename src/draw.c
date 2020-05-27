#include "draw.h"

#include <raylib.h>

void draw_level(const level *lvl){
    // Draw cells, iterate, including borders outside the level
    for(int y=-1;y<=lvl->size_y;y++){
        for(int x=-1;x<=lvl->size_x;x++){
            char cell = level_get(lvl,x,y);
            // If the cell is a wall, paint it
            if(cell=='#'){
                DrawRectangle(TILE_SIZE*x,TILE_SIZE*y,TILE_SIZE,TILE_SIZE,BROWN);
            }
        }
    }
}

void draw_state(const level *lvl, const state *sta, float tim, Vector2 direc, int frame, float framethicc, const Texture2D persona){



    // Initialize a camera to be used as drawing context
    Camera2D cam;
    // make the camera follow the player
    cam.target.x = sta->pla.ent.x;
    cam.target.y = sta->pla.ent.y;
    // make it so that the player is in the middle of the screen
    cam.offset.x = GetScreenWidth()/2.0;
    cam.offset.y = GetScreenHeight()/2.0;
    // set the camera rotation to 0
    cam.rotation = 0.0;
    // set the camera zoom to 1
    cam.zoom = 1.0;



    //Variables to localize animations in the grid, define orientation and relative scale
    float altura1 = 0;
    int invertir = 1;
    Vector2 origen = {0,0};

    //Changing this value increases or decreases the size of the sprites in relation to the entity's radius 
    int escala = 4;


    // Draw everything relative to the camera from now on
    BeginMode2D(cam);

    // Draw level
    draw_level(lvl);

    // Draw enemies
    for(int i=0;i<sta->n_enemies;i++){
        // Get a copy of the enemy entity
        entity ent = sta->enemies[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity, color depends on the enemy type
        if(sta->enemies[i].kind == MINION){
            //DrawCircleV(vec,ent.rad,YELLOW);
            altura1  = 420;
            Rectangle cuadroen1 = {framethicc*frame, altura1, framethicc*invertir, 70};
            Rectangle escalaen1= {vec.x-ent.rad,vec.y-ent.rad,ent.rad*escala,ent.rad*escala};
            DrawTexturePro(persona, cuadroen1, escalaen1, origen, 0, RAYWHITE);
        }else{
            //DrawCircleV(vec,ent.rad,RED);
            altura1 = 490;
            Rectangle cuadroen2 = {framethicc*frame, altura1, framethicc*invertir, 70};
            Rectangle escalaen2 = {vec.x-ent.rad,vec.y-ent.rad,ent.rad*escala,ent.rad*escala};
            DrawTexturePro(persona, cuadroen2, escalaen2, origen, 0, RAYWHITE);
        }
    }

    // Draw player
    {
        // Get a copy of the player's entity
        entity ent = sta->pla.ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circlae with the radius of the entity
        //DrawCircleV(vec,ent.rad,BLUE);


        //idle
        if(direc.x==0 && direc.y==0){
          altura1 = 350;
        }
        //norte
        else if(direc.x==0 && direc.y>0){
          altura1 = 0;
        }
        //noreste
        else if(direc.x>0 && direc.y>0){
          altura1 = 70;
        }
        //este
        else if(direc.x>0 && direc.y==0){
          altura1 = 140;
        }
        //sureste
        else if(direc.x>0 && direc.y<0){
          altura1 = 210;
        }
        //sur
        else if(direc.x==0 && direc.y<0){
          altura1 = 280;
        }
        //suroeste
        else if(direc.x<0 && direc.y<0){
          altura1 = 210;
          invertir = -1;
        }
        //oeste
        else if(direc.x<0 && direc.y==0){
          altura1 = 140;
          invertir = -1;
        }
        //noroeste
        else if(direc.x<0 && direc.y>0){
          altura1 = 70;
          invertir = -1;
        }


        Rectangle cuadro = {framethicc*frame, altura1, framethicc*invertir, 70};
        Rectangle escalaprot = {vec.x-ent.rad,vec.y-ent.rad,ent.rad*escala,ent.rad*escala};
        DrawTexturePro(persona, cuadro, escalaprot, origen, 0, RAYWHITE);
        //DrawTextureRec(persona, cuadro, vec, RAYWHITE);

    }

    // Draw bulletsmak
    for(int i=0;i<sta->n_bullets;i++){
        // Get a copy of the bullet entity
        entity ent = sta->bullets[i].ent;
        // Initialize a Vector2 that represents the center of the entity position
        Vector2 vec = {ent.x,ent.y};
        // Draw a circle with the radius of the entity
        //DrawCircleV(vec,ent.rad,PINK);
        altura1 = 560;
        Rectangle cuadroen2 = {framethicc*frame, altura1, framethicc*invertir, 70};
        Rectangle escalaen2 = {vec.x-ent.rad,vec.y-ent.rad,ent.rad*escala,ent.rad*escala};
        DrawTexturePro(persona, cuadroen2, escalaen2, origen, 0, RAYWHITE);
    }

    // Stop drawing relative to the camera
    EndMode2D();
}
