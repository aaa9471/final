
#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))


float Attack::volume = 1.0;

void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void GameWindow::game_init(){
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./background_level1.jpg");
    background2 = al_load_bitmap("./background_level2.png");
    titlepage = al_load_bitmap("./TitlePage.jpg");
    soundpage = al_load_bitmap("./SoundPage.png");
    levelpage = al_load_bitmap("./LevelPage.png");
    selectleft = al_load_bitmap("./select_left.png");
    selectright = al_load_bitmap("./select_right.png");
    level1noflash = al_load_bitmap("./Level1_noflash.png");
    level1flash = al_load_bitmap("./Level1_flash.png");
    level2noflash = al_load_bitmap("./Level2_noflash.png");
    level2flash = al_load_bitmap("./Level2_flash.png");

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 72, 0);
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 36, 0);

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    //level = new LEVEL(1);
    menu = new Menu();
}

bool GameWindow::mouse_hover(int startx, int starty, int width, int height) //(0, 0, field_width, field_height)
{
    if(mouse_x >= startx && mouse_x <= startx + width) //mouse_x and mouse_y are defined in GameWindow.h::private
        if(mouse_y >= starty && mouse_y <= starty + height) //why don't write in one if?
            return true;

    return false;
}

bool GameWindow::isOnRoad()
{
    int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;
}

Tower* GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isOnRoad())
        return t;

    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y); //the parameter is where to build the tower
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    case BUILTTOWER:
        t = new BuiltTower(mouse_x, mouse_y);
        break;
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type)); //reduce money

    return t;
}

Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;
}

void GameWindow::game_play(){
    int msg;

    srand(time(NULL));

    msg = -1; //template: -1, GAME_INIT
    /*
    *  We start the game by calling game_begin to start timer and play music
    * [TODO]:
    *     You may add some function to create starting scene before calling game_begin
    *     e.g: game_start_scene()
    */

    while(1){
        if(msg==GAME_INIT){
            game_title_page_init();
            msg = GAME_INIT;
            self = GAME_INIT;
            while(msg == GAME_INIT){
                //std::cout << "into while" << std::endl;
                msg = game_title_page_run();
                if(msg!=GAME_INIT) break;
            }
        }
        if(msg==GAME_CONTINUE){
            //std::cout << "dd" << std::endl;
            game_begin(); //game_init
            msg = GAME_CONTINUE;
            self = GAME_CONTINUE;
            while(msg==GAME_CONTINUE){
                msg = game_run();
                if(msg!=GAME_CONTINUE) break;
            }
        }
        if(msg==GAME_LEVEL_2){
            //std::cout << "cc" << std::endl;
            game_level_2_init(); //game_init
            msg = GAME_LEVEL_2;
            self = GAME_LEVEL_2;
            while(msg==GAME_LEVEL_2){
                msg = game_level_2_run();
                if(msg!=GAME_LEVEL_2) break;
            }
        }
        if(msg==GAME_SETTING){
            game_sound_page_init();
            msg = GAME_SETTING;
            self = GAME_SETTING;
            while(msg == GAME_SETTING){
                //std::cout << "into while" << std::endl;
                msg = game_sound_page_run();
                if(msg!=GAME_SETTING) break;
            }
        }
        if(msg==GAME_SELECT){
            game_level_page_init();
            msg = GAME_SELECT;
            self = GAME_SELECT;
            while(msg == GAME_SELECT){
                msg = game_level_page_run();
                if(msg!=GAME_SELECT) break;
            }
            //std::cout << msg << std::endl;
        }
        if(msg==GAME_EXIT){
            game_destroy();
            return ;
        }
    }
    /*
    *  while game is running, the result of game_run will be returned to msg.
    *  If msg is GAME_EXIT, then tower game will terminate.
    */
    //while(msg != GAME_EXIT) //GAME_EXIT==7, define in GameWindow.h
    //    msg = game_run();
    //show_err_msg(msg);
    return ;
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

GameWindow::GameWindow(){ //initialize everything in constructor
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
    monster_pro = al_create_timer(1.0 * 80 / FPS);

    if(timer == NULL || monster_pro == NULL)
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

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    // Initializing resources that tower game needs.

    game_init();
}

void GameWindow::game_begin(){ //level 1 init
    level = new LEVEL(1);
    printf(">>> Start Level[%d]\n", level->getLevel());

    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);
    //al_rest(5.0);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int GameWindow::game_run(){ //level 1 play
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void GameWindow::game_title_page_init(){ //game_begin

    keys = (bool*) malloc(2 * sizeof(bool));
    memset(keys, false, 2 * sizeof(bool));
    pos_y = 300;
    //event_queue_of_titlepage = al_create_event_queue();

    //int error = GAME_INIT;
    al_draw_bitmap(titlepage, 0, 0, 0);
    al_draw_bitmap(selectleft, 175, pos_y, 0);
    al_draw_bitmap(selectright, 525, pos_y, 0);
    al_draw_text(font, WHITE, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE,  "Tower Defense");
    al_draw_text(Medium_font, WHITE, 400.0, 300.0, ALLEGRO_ALIGN_CENTRE,  "Start");
    al_draw_text(Medium_font, WHITE, 400.0, 400.0, ALLEGRO_ALIGN_CENTRE,  "Settings");
    al_draw_text(Medium_font, WHITE, 400.0, 500.0, ALLEGRO_ALIGN_CENTRE,  "Quit");
    al_flip_display();

    return ;
}

int GameWindow::game_title_page_run(){ //game_run
    int error = GAME_INIT;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void GameWindow::game_sound_page_init(){
    std::cout << "into sound init" << std::endl;
    al_draw_bitmap(soundpage, 0, 0, 0);
    al_draw_text(Medium_font, WHITE, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE,  "Settings");
    al_flip_display();
}

int GameWindow::game_sound_page_run(){
    //std::cout << "into sound page" << std::endl;
    int error = GAME_SETTING;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void GameWindow::game_level_page_init(){
    std::cout << "into level init" << std::endl;
    al_draw_bitmap(levelpage, 0, 0, 0);
    al_draw_bitmap(level1noflash, 185, 250, 0);
    al_draw_bitmap(level2noflash, 420, 250, 0);
    al_draw_text(Medium_font, WHITE, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE, "Level");
    //al_play_sample_instance(backgroundSound);
    al_flip_display();
}

int GameWindow::game_level_page_run(){
    //std::cout << "into level page" << std::endl;
    int error = GAME_SELECT;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

void GameWindow::game_level_2_init(){
    level = new LEVEL(2);
    printf(">>> Start Level[%d]\n", level->getLevel());
    draw_running_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
    return ;
}

int GameWindow::game_level_2_run(){
    int error = GAME_LEVEL_2;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int GameWindow::game_update(){
    unsigned int i, j;
    std::list<Tower*>::iterator it;

    /*TODO:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    for(it=towerSet.begin(); it!=towerSet.end(); it++){
        for(j=0; j!=monsterSet.size(); j++){
            if((*it)->DetectAttack(monsterSet[j])==true){
                if(self==GAME_CONTINUE) return GAME_CONTINUE;
                else if(self==GAME_LEVEL_2) return GAME_LEVEL_2;
            }
        }
    }

    // update every monster
    // check if it is destroyed or reaches end point
    for(i=0; i < monsterSet.size(); i++)
    {
        bool isDestroyed = false, isReachEnd = false;
        /*TODO:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/
        for(it=towerSet.begin(); it!=towerSet.end(); it++){
            if((*it)->TriggerAttack(monsterSet[i])) isDestroyed = true;
        }

        isReachEnd = monsterSet[i]->Move();

        if(isDestroyed){
            Monster *m = monsterSet[i];

            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
        else if(isReachEnd){
            Monster *m = monsterSet[i];

            if(menu->Subtract_HP())
                return GAME_EXIT;

            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }

    /*TODO:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    for(it=towerSet.begin(); it!=towerSet.end(); it++){
        (*it)->UpdateAttack();
    }

    if(self==GAME_CONTINUE) return GAME_CONTINUE;
    else if(self==GAME_LEVEL_2) return GAME_LEVEL_2;
}

void GameWindow::game_reset(){
    // clear all towers
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    monsterSet.clear();

    selectedTower = -1;
    lastClicked = -1;
    Coin_Inc_Count = 0;
    mute = false;
    redraw = false;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);

    return ;
}

void GameWindow::game_destroy(){
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_timer(timer);
    al_destroy_timer(monster_pro);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

    delete level;
    delete menu;

    return ;
}

int GameWindow::process_event()
{
    int i;
    int instruction = self;

    Slider bgm(300, 250);
    Slider se(300, 340);

    al_wait_for_event(event_queue, &event);
    redraw = false;


    if(event.type == ALLEGRO_EVENT_TIMER) { //skip this for now
        if(event.timer.source == timer) {
            redraw = true;

            if(Coin_Inc_Count == 0)
                menu->Change_Coin(Coin_Time_Gain);

            Coin_Inc_Count = (Coin_Inc_Count + 1) % CoinSpeed;

            // All monsters are created and destroyed -> Game Exit
            if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro)) //mosterSet.size() is the number of monsters on field
            {
                al_stop_timer(timer);
                //std::cout << "end game" << std::endl;
                if(menu->getHealth()>0 && instruction==GAME_CONTINUE){
                    al_draw_text(font, ORANGE_LIGHT, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE,  "Congratulations!");
                    al_flip_display();
                    al_rest(3);
                    game_reset();
                    return GAME_LEVEL_2;
                }
                else return GAME_EXIT;
            }

        }
        else {
            Monster *m = create_monster();

            if(m != NULL)
                monsterSet.push_back(m);
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { //press the x button
        game_destroy();
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){ //press any key
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_P: //press key P
                /*
                * You can add some variable to control if game is paused.
                * e.g: pause
                * In addition to add variable, you also have to modify draw_running_map() and game_update()
                * Or, monsters and towers can still work without being paused
                */
                break;
            case ALLEGRO_KEY_M: //press key M
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_B:
                game_reset();
                return GAME_INIT;
                break;
        }

        if(instruction==GAME_INIT){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    keys[UP] = true;
                    keys[DOWN] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = true;
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_ENTER:
                    //std::cout << "enter down" <<std::endl;
                    if(pos_y==300) return GAME_SELECT;
                    else if(pos_y==400) return GAME_SETTING;
                    else if(pos_y==500) return GAME_SETTING;
                    break;
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP){
        if(instruction==GAME_INIT){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    keys[UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    keys[DOWN] = false;
                    break;
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) { //press any mouse button
        if(event.mouse.button == 1){ //pressed left mouse button
            // Create tower
            //std::cout << event.mouse.x << " " << event.mouse.y << std::endl;
            if(instruction==GAME_CONTINUE || instruction==GAME_LEVEL_2){
                if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {//a tower in hand //and mouse is in field
                    std::cout << "pressed with a tower in hand" << std::endl;
                    Tower *t = create_tower(selectedTower); //parameter is type of tower

                    if(t == NULL)
                        printf("Wrong place\n");
                    else{
                        towerSet.push_back(t); //towerSet defined in .h
                        towerSet.sort(compare);
                    }
                }
                /*
                *  Check if any tower is clicked.
                *  If so, cancel the shown circle range of the tower.
                *  In addition, we also re-check if any circle range should show up.
                */
                else if(selectedTower == -1){ //no tower in hand (-1 is without a tower)
                    //std::cout << "pressed without a tower in hand" << std::endl;
                    std::list<Tower*>::iterator it = towerSet.begin();
                    if(lastClicked != -1) //??
                    {
                        std::advance(it, lastClicked);
                        (*it)->ToggleClicked();
                    }
                    for(i=0, it = towerSet.begin(); it != towerSet.end(); it++, i++) //skip this for now
                    {
                        Circle *circle = (*it)->getCircle();
                        int t_width = (*it)->getWidth();

                        if(mouse_hover(circle->x - t_width/2, circle->y, t_width, t_width/2))
                        {
                            (*it)->ToggleClicked();
                            lastClicked = i;
                            break;
                        } else {
                            lastClicked = -1;
                        }
                    }
                }
                // check if user wants to create some kind of tower
                // if so, show tower image attached to cursor
                selectedTower = menu->MouseIn(mouse_x, mouse_y);
            }
            else if(instruction==GAME_SETTING){
                if(isClicked(bgm_x, 250, event.mouse.x, event.mouse.y)){ //press on target
                    bgm_x_clicked = true;
                    std::cout << "bgm.toggle" << std::endl;
                }
                else if(isClicked(se_x, 340, event.mouse.x, event.mouse.y)){
                    se_x_clicked = true;
                    std::cout << "se.toggle" << std::endl;
                }
            }
            else if(instruction==GAME_SELECT){
                if(mouse_hover(185, 250, 190, 200)==true) return GAME_CONTINUE;
                else if(mouse_hover(420, 250, 190, 200)==true) return GAME_LEVEL_2;
                //al_draw_bitmap(level1noflash, 185, 250, 0);
                //al_draw_bitmap(level2noflash, 420, 250, 0);
            }
        }
        else if(event.mouse.button==2){ //pressed right mouse button
            //std::cout << "pressed right mouse button" << std::endl;
            menu->Change_Coin(500);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
        if(instruction==GAME_SETTING){
            bgm_x_clicked = false;
            se_x_clicked = false;

            volume_of_bgm = bgm.Drag(bgm_x, 235);
            std::cout << bgm_x << std::endl;
            std::cout << volume_of_bgm << std::endl;
            al_set_sample_instance_gain(backgroundSound, volume_of_bgm);
            al_set_sample_instance_gain(startSound, volume_of_se);

            volume_of_se = se.Drag(se_x, 235);
            std::cout << volume_of_se << std::endl;
            //include all the SEs... //SE cannot be changed volume hereXD
            set_attack_volume(volume_of_se);
            //al_set_sample_gain(sample, volume_of_se);
            //al_set_sample_instance_gain(clearSound, volume_of_se); //include all the SEs...
            //al_set_sample_instance_gain(failSound, volume_of_se); //include all the SEs...
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){ //find where the location of mouse button
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        if(instruction==GAME_SELECT){
            if(mouse_hover(185, 250, 190, 200)==true) level_1_flashed = true;
            else level_1_flashed = false;
            if(mouse_hover(420, 250, 190, 200)==true) level_2_flashed = true;
            else level_2_flashed = false;
        }

        menu->MouseIn(mouse_x, mouse_y);
    }

    if(redraw){
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    if(instruction==GAME_INIT){
        if(pos_y>300) pos_y -= keys[UP] * 100;
        if(pos_y<500) pos_y += keys[DOWN] * 100;

        al_draw_bitmap(titlepage, 0, 0, 0);
        al_draw_bitmap(selectleft, 175, pos_y, 0);
        al_draw_bitmap(selectright, 525, pos_y, 0);
        al_draw_text(font, WHITE, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE,  "Tower Defense");
        al_draw_text(Medium_font, WHITE, 400.0, 300.0, ALLEGRO_ALIGN_CENTRE,  "Start");
        al_draw_text(Medium_font, WHITE, 400.0, 400.0, ALLEGRO_ALIGN_CENTRE,  "Settings");
        al_draw_text(Medium_font, WHITE, 400.0, 500.0, ALLEGRO_ALIGN_CENTRE,  "Quit");
        al_flip_display();
    }
    else if(instruction==GAME_SETTING){
        if(bgm_x>=300 && bgm_x<=500 && bgm_x_clicked==true){
            if(event.mouse.x<300) bgm_x = 300;
            else if(event.mouse.x>500) bgm_x = 500;
            else bgm_x = event.mouse.x;//keys[LEFT]*5;
        }
        if(se_x>=300 && se_x<=500 && se_x_clicked==true){
            if(event.mouse.x<300) se_x = 300;
            else if(event.mouse.x>500) se_x = 500;
            else se_x = event.mouse.x;//keys[LEFT]*5;
        }

        al_draw_bitmap(soundpage, 0, 0, 0);
        al_draw_text(Medium_font, WHITE, 400.0, 100.0, ALLEGRO_ALIGN_CENTRE, "Settings");
        bgm.set_label_content("BGM");
        bgm.Draw();
        se.set_label_content("SE");
        se.Draw();

        al_draw_filled_rectangle(bgm_x, 235, bgm_x + 15, 235 + 30, WHITE);
        al_draw_filled_rectangle(se_x, 325, se_x + 15, 325 + 30, WHITE);

        al_flip_display();
    }
    else if(instruction==GAME_SELECT){
        if(level_1_flashed==true) al_draw_bitmap(level1flash, 185, 250, 0);
        else al_draw_bitmap(level1noflash, 185, 250 ,0);
        if(level_2_flashed==true) al_draw_bitmap(level2flash, 420, 250, 0);
        else al_draw_bitmap(level2noflash, 420, 250 ,0);

        al_flip_display();
    }

    return instruction;
}

void GameWindow::draw_running_map(){
    unsigned int i, j;

    //al_clear_to_color(al_map_rgb(100, 100, 100));
    if(self==GAME_CONTINUE) al_draw_bitmap(background, 0, 0, 0);
    else if(self==GAME_LEVEL_2) al_draw_bitmap(background2, 0, 0, 0);

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

    for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }


    for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();

    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

    al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    menu->Draw();

    al_flip_display();

    return ;
}
