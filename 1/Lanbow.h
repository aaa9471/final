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
        speed = 1;
        position_x = 0;
        position_y = 0;
    }
    void Draw();

};

#endif // LANBOW_H_INCLUDED
