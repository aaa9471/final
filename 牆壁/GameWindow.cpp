#include"GameWindow.h"
#include <bits/stdc++.h>
#include"global.h"
using namespace std;
void GameWindow::game_init()
{
    background = al_load_bitmap(".//template//StartBackground.jpg");
    //sample = al_load_sample();
    Character1 = new Lanbow;
    level = new LEVEL(1);

}
void GameWindow::game_play()
{
    int msg;
    srand(time(NULL));

    msg = -1;
    game_begin();
    while (msg != GAME_EXIT){
        msg = game_run();
    }

}

void GameWindow::game_begin(){
    draw_running_map();
    al_start_timer(timer);
}

void GameWindow::draw_running_map(){
    int i,j;
    al_clear_to_color(al_map_rgb(200,200,100));
    al_draw_bitmap(background, 0, 0, 0);
    for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            sprintf(buffer, "%d", i*15 + j);
            if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }
            // For debug usage, if you want to create a new map, you may turn off this comment.
            // al_draw_text(font, al_map_rgb(0, 0, 0), j*40 + 20, i*40 + 14, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }
    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    Character1->Draw();
    al_flip_display();

}

GameWindow::GameWindow(){

    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    /*
    * Create two timers to control different parts of tower game:
    *    a. timer: control the animation of each object, stopped when game doesn't run.
    *    b. monster_pro: control the production of monster, stooped when there is no need to produce monster.
    */
    timer = al_create_timer(1.0 / FPS);
    if(timer == NULL )
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    //font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initializing resources that tower game needs.
    game_init();
}


int GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;

}

int GameWindow::process_event(){
    int instruction = GAME_CONTINUE;

    al_wait_for_event(event_queue, &event);
    redraw = false;
    if (event.type == ALLEGRO_EVENT_TIMER){
        if (event.timer.source == timer){
            redraw = true;
        }
    }
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (event.keyboard.keycode){
            case ALLEGRO_KEY_W:

                if (Character1->get_y()>0&&level->isRoad(Character1->get_x()/40+(Character1->get_y()-Character1->get_speed())/40*15))Character1->mov_up();
                break;
            case ALLEGRO_KEY_A:
                std::cout << Character1->get_x()/40+Character1->get_y()/40*15+1<< std::endl;
                if (Character1->get_x()>0&&level->isRoad((Character1->get_x()-Character1->get_speed())/40+Character1->get_y()/40*15))Character1->mov_left();
                break;
            case ALLEGRO_KEY_S:
                std::cout << "s" << std::endl;
                cout<<Character1->get_x()/40+Character1->get_y()/40*15+15<<endl;
                if (Character1->get_y()<field_height&&level->isRoad(Character1->get_x()/40+Character1->get_y()/40*15+15))Character1->mov_down();
                break;
            case ALLEGRO_KEY_D:
                if (Character1->get_x()<field_width&&level->isRoad(Character1->get_x()/40+Character1->get_y()/40*15+1))Character1->mov_right();
                break;
            case ALLEGRO_KEY_SPACE:
                break;
            case ALLEGRO_KEY_UP:
                break;
            case ALLEGRO_KEY_LEFT:
                break;
            case ALLEGRO_KEY_DOWN:
                break;
            case ALLEGRO_KEY_RIGHT:
                break;
            case ALLEGRO_KEY_ENTER:
                break;
        }
    }
    else if(event.type==ALLEGRO_EVENT_KEY_UP){

    }

    if(redraw) {
        // update each object in game
        //instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;

}

void GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

void GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);


    al_destroy_timer(timer);

    al_destroy_bitmap(background);

}

void GameWindow::game_reset()
{
    // clear all towers



    redraw = false;


    // stop sample instance


    // stop timer
    al_stop_timer(timer);
}

bool
GameWindow::isOnRoad_y()
{
    int x,y;
    int widthOfTower;

    widthOfTower = 40;
    x = Character1->get_x()/15;

}
