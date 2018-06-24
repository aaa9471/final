#include "WATERBALL.h"
#include <iostream>

void WaterBall::draw(){
    int draw_x = 50;
    int draw_y = 50;
    //std::cout << position_x << std::endl;
    //std::cout << position_y << std::endl;

    waterball = al_load_bitmap("./waterball.png");
    al_draw_bitmap(waterball, draw_x, draw_y, 0);

    return ;
}
