#include "WATERBALL.h"

void WaterBall::Draw(){
    ALLEGRO_BITMAP *waterball = NULL;

    waterball = al_load_bitmap("./blue.png");

    al_draw_bitmap(lanbow, position_x, position_y, 0);
}

