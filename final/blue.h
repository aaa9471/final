#ifndef CLAW_H_INCLUDED
#define CLAW_H_INCLUDED

#include "Player.h"

class Blue : public Player
{
public:
    Player() : Monster(path)
    {
        ball = 2;
        power = 1;
        speed = 1;

    }

};


#endif // CLAW_H_INCLUDED
