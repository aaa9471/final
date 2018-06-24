#include "Lanbow.h"

void Lanbow::Draw(){
    lanbow = al_load_bitmap("./blue.png");

    al_draw_bitmap(lanbow, position_x, position_y, 0);
}

void Lanbow::Draw_captive(){
    lanbow = al_load_bitmap("./blue_captive.png");

    al_draw_bitmap(lanbow, position_x, position_y, 0);
}
