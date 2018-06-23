#include "Lanbow.h"

void
Lanbow::Draw()
{
    ALLEGRO_BITMAP *lanbow = NULL;

    lanbow = al_load_bitmap("./blue.png");

    al_draw_bitmap(lanbow,position_x,position_y,0);
}
