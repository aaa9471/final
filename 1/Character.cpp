#include "Character.h"

const int axix_x[] = {-1,1,0,0};
const int axis_y[] = {0,0,-1,1};


int
Character::mov_up(int position_y)
{
    position_y += speed;
    return position_y;
}

int
Character::mov_down(int position_y)
{
    position_y -= speed;
    return position_y;
}

int
Character::mov_left(int position_x)
{
    position_x -= speed;
    return position_x;
}

int
Character::mov_right(int position__x)
{
    position_x += speed;
    return position_x;
}

