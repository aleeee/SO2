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
    carThreads.push_back(*new pthread_t());
    pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,'x','e',15,25,0,&carThreads.at(carThreads.size()-1),&mutex));
    carThreads.push_back(*new pthread_t());
    pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,'s','n',20,27,0,&carThreads.at(carThreads.size()-1),&mutex));
    carThreads.push_back(*new pthread_t());
    pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,'d','w',17,25,150,&carThreads.at(carThreads.size()-1),&mutex));
    
    //keyboard
    noecho();
    nodelay(stdscr, true);
    while (true) {
        int ch = getch();
        if (ch == ERR) {
            continue;
        }
        else if (ch == 's') {
            pthread_mutex_lock(&mutex);
            if (cros->isStopped == 0) {
                cros->isStopped = 1;
            } else {
                cros->isStopped = 0;
            }
            pthread_mutex_unlock(&mutex);
        }
        else if ( ch == 'u') {
            pthread_mutex_lock(&mutex);
            clear();
            //obsluga zmiany ustawien skrzyzowania
            mvprintw(0, 0, "Pozdrawiam");
            int ch = getch();
            while (ch != 'u') {
                ch = getch();
            }
            cros->drawCrossroad();
            pthread_mutex_unlock(&mutex);
        }
        else {
            break;
        }
    }
    
    pthread_mutex_destroy(&mutex);
    //pthread_exit(0);
    endwin();
    
    delete cros;
    
    return 0;
}

