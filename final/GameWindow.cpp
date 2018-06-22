#include"GameWindow.h"
#include <bits/stdc++.h>
#include"global.h"

void GameWindow::game_init()
{
    background = al_load_bitmap(".//template//background.png");
    //sample = al_load_sample();

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

void GameWindow::game_begin()
{
    draw_running_map();
    al_start_timer(timer);


}
void GameWindow::draw_running_map()
{
    //int i,j;
    al_clear_to_color(al_map_rgb(200,200,100));
    al_draw_bitmap(background, 0, 0, 0);

    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));
    al_flip_display();

}
GameWindow::GameWindow()
{

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

int GameWindow::process_event()
{
    int i;
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


    if(redraw) {
        // update each object in game
        //instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;

}



void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}


void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);


    al_destroy_timer(timer);

    al_destroy_bitmap(background);

}

void
GameWindow::game_reset()
{
    // clear all towers



    redraw = false;


    // stop sample instance


    // stop timer
    al_stop_timer(timer);
}
