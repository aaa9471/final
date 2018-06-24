#include "Cunbow.h"

void Cunbow::Draw(){
    cunbow = al_load_bitmap("./red.png");

    al_draw_bitmap(cunbow, position_x, position_y, 0);
}

void Cunbow::Draw_captive(){
    cunbow = al_load_bitmap("./red_captive.png");

    al_draw_bitmap(cunbow, position_x, position_y, 0);
}
