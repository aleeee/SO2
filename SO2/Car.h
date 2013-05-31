//
//  Car.h
//  SO2
//
//  Created by Tomasz on 28.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#ifndef __SO2__Car__
#define __SO2__Car__

#include <iostream>
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>

class Car {
private:
    char symbol;
    char destination;
    int speed;
    int yCord;
    int xCord;
    pthread_mutex_t *mutex;
public:
    Car(char,char,int,int,int,pthread_mutex_t*);
    static void *move(void *ptr) {
        Car *thisCar = reinterpret_cast<Car *>(ptr);
        for (int i = 0; i < 50; ++i) {
            pthread_mutex_lock(thisCar->mutex);
            mvprintw(thisCar->yCord, thisCar->xCord, " ");
            if (thisCar->destination == 'w') {
                thisCar->xCord++;
            } else if (thisCar->destination == 'e') {
                thisCar->xCord--;
            }
            
            mvprintw(thisCar->yCord, thisCar->xCord, "x");
            refresh();
            pthread_mutex_unlock(thisCar->mutex);
            usleep(thisCar->speed*1000);
        }
        return NULL;
    };
};

#endif /* defined(__SO2__Car__) */
