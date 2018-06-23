#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>
#include "level.h"
//#include "Player.h"
#include "Character.h" //***
#include "Lanbow.h"
#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

const float FPS = 60;

class GameWindow
{
public:
    GameWindow();
//    ~GameWindow;
    void game_init();
    void game_destroy();
    void game_play();
    void game_begin();
    void draw_running_map();
    int game_run();
    int process_event();
    void show_err_msg(int msg);
    void game_reset();


private:
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    LEVEL *level = NULL;
    Character* player1 = NULL;
    Character* player2 = NULL;
    bool redraw = false;

    int p1x, p1y, p2x, p2y;

    //ALLEGRO_BITMAP *lanbow = NULL;
};





#endif