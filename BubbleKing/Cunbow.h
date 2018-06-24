#ifndef CUNBOW_H_INCLUDED
#define CUNBOW_H_INCLUDED

#include "Character.h"

class Cunbow : public Character
{
public:
    Cunbow() : Character()
    {
        ball = 1;
        power = 1;
        speed = 1;
        position_x = 160;
        position_y = 160;
    }
    void Draw();
    void Draw_captive();

private:
    ALLEGRO_BITMAP *cunbow = NULL;

};

#endif // LANBOW_H_INCLUDED
