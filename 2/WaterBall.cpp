#include "WATERBALL.h"

void WaterBall::Draw(){
    ALLEGRO_BITMAP *waterball = NULL;

    waterball = al_load_bitmap("./waterball.png");

    al_draw_bitmap(waterball, position_x, position_y, 0);

    return ;
}

