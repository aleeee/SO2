//
//  Crossroad.h
//  SO2
//
//  Created by Tomasz on 25.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#ifndef __SO2__Crossroad__
#define __SO2__Crossroad__

#include <iostream>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>
#include "Light.h"

class Crossroad {
private:
    int xRange;// = 204;
    int yRange;// = 63;
    pthread_t thread;
    pthread_mutex_t *mutex;
public:
    Crossroad(Light *);
    ~Crossroad();
    void drawCrossroad();
    void initStructureOfCrossroad();
    int isStopped;
    int isQuited;
    int **crossRoadStructure;
    int **carsWithDirections;
    int **roadsDirections;
    int crashCount;
    bool check(char,int);
    bool isAllowed(int,int,char);
    bool isGreenLight(int,int);
    Light *lights;
};

#endif /* defined(__SO2__Crossroad__) */
