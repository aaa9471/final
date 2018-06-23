#ifndef WATERBALL_H_INCLUDED
#define WATERBALL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

enum {LEFT=0, RIGHT, UP, DOWN};

class WaterBall
{
public:
    WATERBALL(){};
    ~WATERBALL();

    void draw();

protected:
    int position_x;
    int position_y;
};

#endif // WATERBALL_H_INCLUDED
