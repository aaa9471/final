#include"GameWindow.h"
#include <bits/stdc++.h>
#include"global.h"
using namespace std;
void GameWindow::game_init()
{
    background = al_load_bitmap(".//template//StartBackground.jpg");
    waterball = al_load_bitmap("./waterball.png");
    waterball_blow = al_load_bitmap("./waterballblow.png");
    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 72, 0);

    //sample = al_load_sample();
    player1 = new Lanbow;
    player2 = new Cunbow;
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
            /*if(level->isRoad(i*15 + j)) {
                al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
            }*/
            // For debug usage, if you want to create a new map, you may turn off this comment.
            // al_draw_text(font, al_map_rgb(0, 0, 0), j*40 + 20, i*40 + 14, ALLEGRO_ALIGN_CENTER, buffer);
        }
    }
    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    //for(vector<WaterBall*>::iterator it = waterballSet.begin(); it != waterballSet.end(); it++)
    //    (*it)->Draw();
    for(int i=0; i<10; i++){
        if(waterball_array[i]==1){
            al_draw_bitmap(waterball, waterball_x[i], waterball_y[i], 0);
            there_is_a_waterball = true;
        }
    }
    for(int i=0; i<10; i++){
        if(waterball_array[i]==1){
            al_draw_bitmap(waterball, waterball_x[i], waterball_y[i], 0);
            there_is_a_waterball = true;
        }
    }
    if(waterball_blowing==true){
        for(int i=0; i<10; i++){
            if(waterball_array[i]==1){
                al_draw_bitmap(waterball_blow, waterball_x[i]-40, waterball_y[i]-40, 0);
            }
        }
    }

    if(player1_captive==true) player1->Draw_captive();
    else player1->Draw();
    if(player2_captive==true) player2->Draw_captive();
    else player2->Draw();

    if(player1_win==true) al_draw_text(font, al_map_rgb(255, 255, 255), 50.0, 50.0, 0, "Lanbow Wins!");
    else if(player2_win==true) al_draw_text(font, al_map_rgb(255, 255, 255), 50.0, 50.0, 0, "Cunbow Wins!");

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


int GameWindow::game_run(){
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;

}

int GameWindow::process_event(){
    int instruction = GAME_CONTINUE;
    int future_x, future_y;
    int future2_x, future2_y;
    future_x = player1->position_x + player1->right * player1->get_speed() - player1->left * player1->get_speed();
    future_y = player1->position_y + player1->down * player1->get_speed() - player1->up * player1->get_speed();
    future2_x = player2->position_x + player2->right * player2->get_speed() - player2->left * player2->get_speed();
    future2_y = player2->position_y + player2->down * player2->get_speed() - player2->up * player2->get_speed();
    if (isonroad(future_x,future_y)){
        player1->position_x = future_x;
        player1->position_y = future_y;
    }
    if (isonroad2(future2_x,future2_y)){
        player2->position_x = future2_x;
        player2->position_y = future2_y;
    }

    if(there_is_a_waterball==true){
        counter2-=1;
    }
    if(counter2<=0){
        std::cout << "count_down_finish" << std::endl;
        /*for(int i=0; i<10; i++){
            if(waterball_array[i]==1){
                al_draw_bitmap(waterball_blow, waterball_x[i], waterball_y[i], 0);
                waterball_array[i] = 0;
                waterball_x[i] = 0;
                waterball_y[i] = 0;
            }
        }*/
        there_is_a_waterball = false;
        waterball_blowing = true;
        counter2 = 200;
    }
    if(waterball_blowing==true){
        counter3-=1;
        for(int i=0; i<10; i++){
            if(player1->get_x()>waterball_x[i]-40 && player1->get_x()<waterball_x[i]+80){
                if(player1->get_y()>waterball_y[i]-40 && player1->get_y()<waterball_y[i]+80){
                    player1_captive = true;
                    player1->change_speed();
                }
            }
            if(player2->get_x()>waterball_x[i]-40 && player2->get_x()<waterball_x[i]+80){
                if(player2->get_y()>waterball_y[i]-40 && player2->get_y()<waterball_y[i]+80){
                    player2_captive = true;
                    player2->change_speed();
                }
            }
        }
    }
    if(counter3<=0){
        std::cout << "waterball_blowing_finish" << std::endl;
        waterball_blowing = false;
        for(int i=0; i<10; i++){
            if(waterball_array[i]==1){
                al_draw_bitmap(waterball_blow, waterball_x[i], waterball_y[i], 0);
                waterball_array[i] = 0;
                waterball_x[i] = 0;
                waterball_y[i] = 0;
            }
        }
        counter3 = 50;
    }

    if(player1_captive==true){
        if(player2->position_x<player1->position_x+40 && player2->position_x>player1->position_x-40){
            if(player2->position_y<player1->position_y+40 && player2->position_y>player1->position_y-40){
                player2_win = true;
            }
        }
    }
    if(player2_captive==true){
        if(player1->position_x<player2->position_x+40 && player1->position_x>player2->position_x-40){
            if(player1->position_y<player2->position_y+40 && player1->position_y>player2->position_y-40){
                player1_win = true;
            }
        }
    }

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
                player1->up = true;
                break;
            case ALLEGRO_KEY_A:
                player1->left = true;
                break;
            case ALLEGRO_KEY_S:
                player1->down = true;
                break;
            case ALLEGRO_KEY_D:
                player1->right = true;
                break;
            /*case ALLEGRO_KEY_SPACE:
                break;*/
            case ALLEGRO_KEY_UP:
                player2->up = true;
                break;
            case ALLEGRO_KEY_LEFT:
                player2->left = true;
                break;
            case ALLEGRO_KEY_DOWN:
                player2->down = true;
                break;
            case ALLEGRO_KEY_RIGHT:
                player2->right = true;
                break;
            /*case ALLEGRO_KEY_ENTER:
                break;*/
        }
    }
    else if(event.type==ALLEGRO_EVENT_KEY_UP){
        switch (event.keyboard.keycode)
        {
        case ALLEGRO_KEY_W:
            std::cout << "w" << std::endl;
            player1->up = false;
            break;
        case ALLEGRO_KEY_A:
            std::cout << "a" << std::endl;
            player1->left = false;
            break;
        case ALLEGRO_KEY_S:
            std::cout << "s" << std::endl;
            player1->down = false;
            break;
        case ALLEGRO_KEY_D:
            std::cout << "d" << std::endl;
            player1->right = false;
            break;
        case ALLEGRO_KEY_SPACE:
            std::cout << "space up" << std::endl;
            //WaterBall *temp = new WaterBall(); //parameter is type of tower
            //waterballSet.push_back(temp); //towerSet defined in .h
            counter1 = 0;
            while(1){
                if(waterball_array[counter1]==0){
                    waterball_array[counter1]=1;
                    waterball_x[counter1] = player1->get_x();
                    waterball_y[counter1] = player1->get_y();

                    break;
                }
                else counter1+=1;
            }
            break;
        case ALLEGRO_KEY_UP:
            std::cout << "up" << std::endl;
            player2->up = false;
            break;
        case ALLEGRO_KEY_LEFT:
            std::cout << "left" << std::endl;
            player2->left = false;
            break;
        case ALLEGRO_KEY_DOWN:
            std::cout << "down" << std::endl;
            player2->down = false;
            break;
        case ALLEGRO_KEY_RIGHT:
            std::cout << "right" << std::endl;
            player2->right = false;
            break;
        case ALLEGRO_KEY_ENTER:
            std::cout << "enter" << std::endl;
            //WaterBall *temp = new WaterBall(); //parameter is type of tower
            //waterballSet.push_back(temp); //towerSet defined in .h
            counter1 = 0;
            while(1){
                if(waterball_array[counter1]==0){
                    waterball_array[counter1]=1;
                    waterball_x[counter1] = player2->get_x();
                    waterball_y[counter1] = player2->get_y();

                    break;
                }
                else counter1+=1;
            }
            break;
        }
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

bool GameWindow::isonroad(int x,int y)
{
    int i = (x/40)+((y+1)/40)*15;

    if (x<0||x>field_width-40||y<0||y+40>field_height)return false;
    if (player1->right&&x%40!=0)i +=1;
    if (player1->left&&(x+1)%40==0)i -= 1;
    if (player1->up&&(y+1)%40==0)i -=15;
    if (player1->down&&(y)%40!=0) i += 15;

    cout<<x<<" "<<y<<" "<<i<<endl;
    if (x%40!=0){
        if (!level->isRoad(i)||!level->isRoad(i+1))return false;
    }
    if (y%40!=0&&(player1->right||player1->left)){
        if (!level->isRoad(i)||!level->isRoad(i+1))return false;
    }
    if (!level->isRoad(i))return false;
    return true;
    /*else if (x%40!=0||y%40!=0){

    }*/
}

bool GameWindow::isonroad2(int x,int y)
{
    int i = (x/40)+((y+1)/40)*15;

    if (x<0||x>field_width-40||y<0||y+40>field_height)return false;
    if (player2->right&&x%40!=0)i +=1;
    if (player2->left&&(x+1)%40==0)i -= 1;
    if (player2->up&&(y+1)%40==0)i -=15;
    if (player2->down&&(y)%40!=0) i += 15;

    //cout<<x<<" "<<y<<" "<<i<<endl;
    if (x%40!=0){
        if (!level->isRoad(i)||!level->isRoad(i+1))return false;
    }
    if (y%40!=0&&(player2->right||player2->left)){
        if (!level->isRoad(i)||!level->isRoad(i+1))return false;
    }
    if (!level->isRoad(i))return false;
    return true;
    /*else if (x%40!=0||y%40!=0){

    }*/
}
