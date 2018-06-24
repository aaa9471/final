#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"

enum {LEFT=0, RIGHT, UP, DOWN};

class Character : public Object
{
public:
    Character(){};
    ~Character();

    void Draw()=0;
    virtual void Draw_captive()=0;

    void mov_up();
    void mov_down();
    void mov_left();
    void mov_right();

    int get_ball() {return ball;}
    int get_power() {return power;}
    int get_speed() {return speed;}
    int get_x(){return position_x;}
    int get_y(){return position_y;}

    bool up = false;
    bool down = false;
    bool right = false;
    bool left = false;

    int position_x;
    int position_y;

protected:
    int ball=1;
    int power = 1;
    int speed =1;
};

#endif // CHARACTER_H_INCLUDED
