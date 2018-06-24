#ifndef LANBOW_H_INCLUDED
#define LANBOW_H_INCLUDED

#include "Character.h"

class Lanbow : public Character
{
public:
    Lanbow() : Character()
    {
        ball = 1;
        power = 1;
        speed = 20;
        position_x = 40;
        position_y = 40;
    }
    void Draw();
    void Draw_captive();

private:
    ALLEGRO_BITMAP *lanbow = NULL;

};

#endif // LANBOW_H_INCLUDED
