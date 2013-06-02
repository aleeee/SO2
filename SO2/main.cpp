//
//  main.cpp
//  SO2
//
//  Created by Tomasz on 22.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include "Crossroad.h"
#include "Car.h"

int main(int argc, const char * argv[])
{
    int threadStackPointer = 0;
    
    std::vector<pthread_t> carThreads;
    
    
    initscr();
    raw();
    curs_set(0);
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    
    Crossroad *cros = new Crossroad();
    
    pthread_mutex_lock(&mutex);
    cros->drawCrossroad();
    pthread_mutex_unlock(&mutex);
    usleep(1000);
    carThreads.push_back(*new pthread_t());
    pthread_create(&carThreads.at(threadStackPointer), NULL, Car::move, new Car(cros,'s','w',15,25,0,&mutex));
    usleep(500);
    
    noecho();
    nodelay(stdscr, true);
    while (true) {
        int ch = getch();
        if (ch == ERR) {
            continue;
        }
        else if (ch == 's') {
            if (cros->isStopped == 0) {
                cros->isStopped = 1;
            } else {
                cros->isStopped = 0;
            }
        }
        else {
            break;
        }
    }
    
    
    mvprintw(0, 0, "Kurwa");
    pthread_mutex_destroy(&mutex);
    endwin();
    
    delete cros;
    
    return 0;
}

