#include "Character.h"

const int axix_x[] = {-1,1,0,0};
const int axis_y[] = {0,0,-1,1};

void Character::mov_up(){
    position_y -= speed;
    return ;
}

void Character::mov_down(){
    position_y += speed;
    return ;
}

void Character::mov_left(){
    position_x -= speed;
    return ;
}

void Character::mov_right(){
    position_x += speed;
    return ;
}
