
#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "global.h"

typedef struct Node {
    int h, g, f;
    bool roadPoint;
}Node;

class LEVEL {
public:
    LEVEL(const int);
    ~LEVEL();

    void setLevel(const int);
    bool isRoad(int index) { return levelMap[index].roadPoint; }
    int getLevel() { return level; }
    //void search_destination();
    std::vector<int> ReturnPath() { return road_grid; }

private:
    Node levelMap[NumOfGrid];
    std::vector<int> road_grid;
    // current level number
    int level = 1;
    // maximum number of monster of a level
};


#endif // LEVEL_H_INCLUDED
