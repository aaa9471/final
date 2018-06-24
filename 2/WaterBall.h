#ifndef WATERBALL_H_INCLUDED
#define WATERBALL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>

#include "Lanbow.h"
#include "Object.h"
#include "Character.h"

class WaterBall : public Character
{
public:
    WaterBall(){};
    //~WATERBALL();

    void draw();

protected:
    ALLEGRO_BITMAP *waterball = NULL;
};

#endif // WATERBALL_H_INCLUDED
