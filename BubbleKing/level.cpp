#include "level.h"

LEVEL::LEVEL(const int level) {
    char buffer[50];

    setLevel(level);
}

LEVEL::~LEVEL()
{
    for(int i=0;i < NumOfGrid;i++)
    {
        levelMap[i].roadPoint = false;
    }
}

void
LEVEL::setLevel(const int level)
{
    char buffer[50];
    FILE *file;

    sprintf(buffer, "LEVEL%d.txt", level);
    file = fopen(buffer, "r");

    this->level = level;
    this->road_grid.clear();

    for(int i = 0; i < NumOfGrid; i++)
    {
        this->levelMap[i].roadPoint = false;
    }

    fscanf(file, "%s", buffer);
    //Monster_MAX = atoi(buffer);



    while(fscanf(file, "%s", buffer) != EOF) {
        this->levelMap[atoi(buffer)].roadPoint = true;
        road_grid.push_back(atoi(buffer));
    }
    fclose(file);
}

