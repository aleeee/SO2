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
    int speed;
    char destination;
    int yCord;
    int xCord;
    bool isOnCrossroad;
    bool isInTheMiddleOfCrossroad;
    pthread_t *thisCarThread;
    pthread_mutex_t *mutex;
    Crossroad *cros;
    char getCurrentDirection() {
        this->isInTheMiddleOfCrossroad = false;
        if (this->xCord < 50) {
            if (this->yCord < 24) {
                return 'w';
            } else {
                return 'e';
            }
        } else if (this->xCord > 70) {
            if (this->yCord < 26) {
                return 'w';
            } else {
                return 'e';
            }
        } else if (this->yCord < 20) {
            if (this->xCord < 60) {
                return 's';
            } else {
                return 'n';
            }
        } else if (this->yCord > 30) {
            if (this->xCord < 55) {
                return 'n';
            } else {
                return 's';
            }
        } else {
            //middle of the crossroad
            this->isInTheMiddleOfCrossroad = true;
            switch (this->destination) {
                case 'n': {
                    if (this->xCord > 62) {
                        if ((this->xCord == 68)||(this->xCord == 73)) {
                            return 'n';
                        } else {
                            return 'e';
                        }
                    } else {
                        return 'e';
                    }
                }
                case 's': {
                    if (this->xCord < 62) {
                        if ((this->xCord == 58)||(this->xCord == 53)) {
                            return 's';
                        } else {
                            return 'w';
                        }
                    } else {
                        return 'w';
                    }
                }
                case 'e': {
                    if (this->yCord > 26) {
                        return 'e';
                    } else {
                        return 's';
                    }
                    break;
                }
                case 'w': {
                    if (this->yCord < 24) {
                        return 'w';
                    } else {
                        return 'n';
                    }
                    break;
                }
            }
        }
        
        return NULL;
    };
public:
    Car(Crossroad *,char,char,int,int,int,pthread_t*,pthread_mutex_t*);
    static void *move(void *ptr) {
        Car *thisCar = reinterpret_cast<Car *>(ptr);
        while (true) {
            pthread_mutex_lock(thisCar->mutex);
            if (!thisCar->cros->isStopped) {
                mvprintw(1, 0, "            ");
                int oldY = thisCar->yCord;
                int oldX = thisCar->xCord;
                
                //movement
                switch (thisCar->getCurrentDirection()) {
                    case 'e': {
                        thisCar->xCord++;
                        break;
                    }
                    case 'w': {
                        thisCar->xCord--;
                        break;
                    }
                    case 's': {
                        thisCar->yCord++;
                        break;
                    }
                    case 'n': {
                        thisCar->yCord--;
                        break;
                    }
                }
                
                mvprintw(thisCar->yCord, thisCar->xCord, &thisCar->symbol);
                mvprintw(oldY, oldX, " ");
                thisCar->cros->crossRoadStructure[oldY][oldX] = ' ';
                if ((thisCar->yCord < 64)&&(thisCar->xCord < 205)&&(thisCar->yCord > -1)&&(thisCar->xCord > -1)) {
                    if (thisCar->cros->crossRoadStructure[thisCar->yCord][thisCar->xCord] == 'c') {
                        mvprintw(1, 0, "Zderzenie!!!");
                        thisCar->cros->crashCount++;
                        char *converter = new char[5];
                        sprintf(converter, "%d", thisCar->cros->crashCount);
                        mvprintw(0, 15, converter);
                        thisCar->cros->isStopped = true;
                    }
                    thisCar->cros->crossRoadStructure[thisCar->yCord][thisCar->xCord] = 'c';
                } else {
                    pthread_cancel(*thisCar->thisCarThread);
                    //thisCar->thisCarThread->pthread_exit(NULL);
                }
            }
            if (thisCar->cros->isQuited) {
                break;
            }
            pthread_mutex_unlock(thisCar->mutex);
            usleep(thisCar->speed*1500);
        }
        return NULL;
    };
};

#endif /* defined(__SO2__Car__) */
