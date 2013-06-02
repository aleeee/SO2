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
#include "Crossroad.h"

class Car {
private:
    char symbol;
    char destination;
    int speed;
    int yCord;
    int xCord;
    pthread_mutex_t *mutex;
    Crossroad *cros;
public:
    Car(Crossroad *,char,char,int,int,int,pthread_mutex_t*);
    static void *move(void *ptr) {
        Car *thisCar = reinterpret_cast<Car *>(ptr);
        while (true) {
            if (!thisCar->cros->isStopped) {
                mvprintw(thisCar->yCord, thisCar->xCord, " ");
                if (thisCar->destination == 'w') {
                    thisCar->xCord++;
                } else if (thisCar->destination == 'e') {
                    thisCar->xCord--;
                }
                
                pthread_mutex_lock(thisCar->mutex);
                mvprintw(thisCar->yCord, thisCar->xCord, "x");
                pthread_mutex_unlock(thisCar->mutex);
                usleep(thisCar->speed*1000);
                refresh();
            }
            if (thisCar->cros->isQuited) {
                break;
            }
        }
        return NULL;
    };
};

#endif /* defined(__SO2__Car__) */
