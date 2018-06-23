#ifndef MONSTER_H_INCLUDED
#define MONSTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>


enum {LEFT=0, RIGHT, UP, DOWN};

class Player/*: public Object*/ {
public:
    Player();
    ~Player();
    void Draw();
    int get_ball();
    int get_power();
    int get_speed();
private:
    int ball = 1;
    int power = 1;
    int speed = 1;


};


#endif // MONSTER_H_INCLUDED

