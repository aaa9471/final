#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

enum {LEFT=0, RIGHT, UP, DOWN};

class Character
{
public:
    Character(){};
    ~Character();

    virtual void Draw()=0;

    //int mov_up(int position_y);
    void mov_up();
    //int mov_down(int position_y);
    void mov_down();
    //int mov_left(int position_x);
    void mov_left();
    //int mov_right(int position_x);
    void mov_right();

    int get_ball() {return ball;}
    int get_power() {return power;}
    int get_speed() {return speed;}

protected:
    int ball=1;
    int power = 1;
    int speed =1;
    int position_x;
    int position_y;

};

#endif // CHARACTER_H_INCLUDED
