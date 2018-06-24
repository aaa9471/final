#include "GameWindow.h"

int main(int argc, char *argv[])
{
    GameWindow *BubbleKing = new GameWindow();

    BubbleKing->game_play();

    delete BubbleKing;
    return 0;
}
