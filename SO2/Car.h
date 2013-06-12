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
    char source;
    int yCord;
    int xCord;
    bool isOnCrossroad;
    bool isInTheMiddleOfCrossroad;
    bool directionSet;
    pthread_t *thisCarThread;
    pthread_mutex_t *mutex;
    Crossroad *cros;
    static char randomDest(char ch) {
        int x = rand()%4;
        
        if (x == 0) {
            if (ch != 'n')
                return 'n';
            else
                return randomDest('n');
        } else if (x == 1) {
            if (ch != 's')
                return 's';
            else
                return randomDest('s');
        } else if (x == 2) {
            if (ch != 'e')
                return 'e';
            else
                return randomDest('e');
        } else {
            if (ch != 'w')
                return 'w';
            else
                return randomDest('w');
        }
    };
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
            if (this->xCord < 60) {
                return 's';
            } else {
                return 'n';
            }
        } else {
            if (!directionSet) {
                while (!this->cros->isAllowed(this->yCord, this->xCord, this->destination)) {
                    mvprintw(0, 0, "pozdrawiam");
                    this->destination = randomDest(this->destination);
                }
                directionSet = true;
            }
            //middle of the crossroad
            this->isInTheMiddleOfCrossroad = true;
            switch (this->destination) {
                case 'n': {
                    if ((this->xCord == 70)||(this->xCord == 69)) {
                        return 'w';
                    } else if (this->xCord > 63) {
                        if ((this->xCord == 68)||(this->xCord == 64)) {
                            return 'n';
                        } else {
                            return 'e';
                        }
                    } else {
                        return 'e';
                    }
                }
                case 's': {
                    if ((this->xCord == 50)||(this->xCord == 51)) {
                        return 'e';
                    } if (this->xCord < 57) {
                        if ((this->xCord == 56)||(this->xCord == 52)) {
                            return 's';
                        } else {
                            return 'w';
                        }
                    } else {
                        return 'w';
                    }
                }
                case 'e': {
                    if (this->yCord == 30) {
                        return 'n';
                    } else if (this->yCord < 27) {
                        return 's';
                    } else {
                        if (this->yCord == 28) {
                            return 's';
                        } else {
                            return 'e';
                        }
                    }
                    break;
                }
                case 'w': {
                    if (this->yCord == 20) {
                        return 's';
                    } else if (this->yCord > 23) {
                        return 'n';
                    } else {
                        if (this->yCord == 22) {
                            return 'n';
                        } else {
                            return 'w';
                        }
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
        while (thisCar->isOnCrossroad) {
            pthread_mutex_lock(thisCar->mutex);
            if (!thisCar->cros->isStopped) {
                mvprintw(1, 0, "            ");
                int oldY = thisCar->yCord;
                int oldX = thisCar->xCord;
                
                //movement
                //tu bedzie duzo jebania - trzeba napisac funkcje ktora bedzie wyciagac wskaznik na auto na podstawie wspolrzednych, zeby moglo zwolnic do predkosci taka jaka ma auto przed nim jak je dogoni
                //ewentualnie samo wyprzedzanie, to bedzie duuuzo latwiejsze ale idzie sie jebac cala idea trzymania sie jednego pasa, bo auto moze nie zdazyc wyprzedzic
                //z drugiej kurwa strony, do wyprzedzania + ogarnianie tego czy zdazy wrocic na swoj pas trzeba by dojebac w pizdu konkretny algorytm obliczania tego, wiec chyba najbardziej prawdopodobny zamysl jest taki, zeby wyprzedzac i miec wyjebane na to, na jakim pasie sie wczesniej bylo i potemlosowac nowe destination z tego na jakim pasie sie znajduje i tez wczesniej w ogole nie patrzec na to jakie bylo pierwotne, chociaz tu sie pojawia kolejny problem, bo moze byc opcja taka, ze nie bedzie jak wyprzedzic, wtedy i tak musi byc ta funkcja sluzaca do zwalniania
                //ale ogolnie pozytywne jest to, ze jak skoncze to + kontrole drogi a to bedzie dosc latwe to mam projekt juz raczej gotowy
                //jednak bez zmieniania predkosci, bedzie samo zwalnianie, dosc sztuczne ale trudno
                switch (thisCar->getCurrentDirection()) {
                    case 'e': {
                        if (thisCar->xCord+1 < 204) {
                            if (thisCar->cros->crossRoadStructure[thisCar->yCord][thisCar->xCord+1] == ' ') {
                                thisCar->xCord++;
                            } else if ((thisCar->isInTheMiddleOfCrossroad)&&(thisCar->cros->carsWithDirections[thisCar->yCord][thisCar->xCord+1] != thisCar->source)) {
                                updateCrash(thisCar);
                                if (thisCar->yCord != 20) {
                                    thisCar->yCord--;
                                } else {
                                    thisCar->yCord++;
                                }
                                
                            } else if (!thisCar->isInTheMiddleOfCrossroad) {
                                //zmiana pasa 
                            }
                        } else {
                            thisCar->xCord++;
                        }
                        break;
                    }
                    case 'w': {
                        if (thisCar->xCord-1 > -1) {
                            if (thisCar->cros->crossRoadStructure[thisCar->yCord][thisCar->xCord-1] == ' ') {
                                thisCar->xCord--;
                            } else if ((thisCar->isInTheMiddleOfCrossroad)&&(thisCar->cros->carsWithDirections[thisCar->yCord][thisCar->xCord-1] != thisCar->source)) {
                                updateCrash(thisCar);
                                if (thisCar->yCord != 30) {
                                    thisCar->yCord--;
                                } else {
                                    thisCar->yCord++;
                                }
                            }
                        } else {
                            thisCar->xCord--;
                        }
                        break;
                    }
                    case 's': {
                        if (thisCar->yCord+1 < 63) {
                            if (thisCar->cros->crossRoadStructure[thisCar->yCord+1][thisCar->xCord] == ' ') {
                                thisCar->yCord++;
                            } else if ((thisCar->isInTheMiddleOfCrossroad)&&(thisCar->cros->carsWithDirections[thisCar->yCord+1][thisCar->xCord] != thisCar->source)) {
                                updateCrash(thisCar);
                                if (thisCar->xCord != 50) {
                                    thisCar->xCord--;
                                } else {
                                    thisCar->xCord++;
                                }
                            }
                        } else {
                            thisCar->yCord++;
                        }
                        break;
                    }
                    case 'n': {
                        if (thisCar->yCord-1 > -1) {
                            if (thisCar->cros->crossRoadStructure[thisCar->yCord-1][thisCar->xCord] == ' ') {
                                thisCar->yCord--;
                            } else if ((thisCar->isInTheMiddleOfCrossroad)&&(thisCar->cros->carsWithDirections[thisCar->yCord-1][thisCar->xCord] != thisCar->source)) {
                                updateCrash(thisCar);
                                if (thisCar->yCord != 70) {
                                    thisCar->yCord--;
                                } else {
                                    thisCar->yCord++;
                                }
                            }
                        } else {
                            thisCar->yCord--;
                        }
                        break;
                    }
                }
                thisCar->cros->crossRoadStructure[oldY][oldX] = ' ';
                thisCar->cros->carsWithDirections[oldY][oldX] = ' ';
                mvprintw(oldY, oldX, " ");
                if ((thisCar->yCord < 63)&&(thisCar->xCord < 204)&&(thisCar->yCord > -1)&&(thisCar->xCord > -1)) {
                    mvprintw(thisCar->yCord, thisCar->xCord, &thisCar->symbol);
                    thisCar->cros->crossRoadStructure[thisCar->yCord][thisCar->xCord] = 'c';
                    thisCar->cros->carsWithDirections[thisCar->yCord][thisCar->xCord] = thisCar->source;
                } else {
                    thisCar->isOnCrossroad = false;
                    //pthread_cancel(*thisCar->thisCarThread);
                    //pthread_exit(0);
                }
            }
            if (thisCar->cros->isQuited) {
                break;
            }
            pthread_mutex_unlock(thisCar->mutex);
            usleep(thisCar->speed*2000);
        }
        return NULL;
    };
    static void updateCrash(Car *thisCar) {
        //mvprintw(1, 0, "Zderzenie!!!");
        thisCar->cros->crashCount++;
        char *converter = new char[5];
        sprintf(converter, "%d", thisCar->cros->crashCount);
        mvprintw(0, 15, converter);
        //thisCar->cros->isStopped = true;
    }
};

#endif /* defined(__SO2__Car__) */
