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
#include "Light.h"

char randomDest(char ch) {
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

void randomCoords(int &y, int &x, char &dest){
    int r = rand()%12;
    switch (r) {
        case 0: {
            x = 0;
            y = 25;
            dest = randomDest('w');
            break;
        }
        case 1: {
            x = 0;
            y = 27;
            dest = randomDest('w');
            break;
        }
        case 2: {
            x = 0;
            y = 29;
            dest = randomDest('w');
            break;
        }
        case 3: {
            x = 203;
            y = 21;
            dest = randomDest('e');
            break;
        }
        case 4: {
            x = 203;
            y = 23;
            dest = randomDest('e');
            break;
        }
        case 5: {
            x = 203;
            y = 25;
            dest = randomDest('e');
            break;
        }
        case 6: {
            x = 52;
            y = 0;
            dest = randomDest('n');
            break;
        }
        case 7: {
            x = 56;
            y = 0;
            dest = randomDest('n');
            break;
        }
        case 8: {
            x = 60;
            y = 0;
            dest = randomDest('n');
            break;
        }
        case 9: {
            x = 60;
            y = 62;
            dest = randomDest('s');
            break;
        }
        case 10: {
            x = 64;
            y = 62;
            dest = randomDest('s');
            break;
        }
        case 11: {
            x = 68;
            y = 62;
            dest = randomDest('s');
            break;
        }
    }
}

int numFromChar(char ch) {
    if (ch == '0') {
        return 0;
    } else if (ch == '1') {
        return 1;
    } else if (ch == '2') {
        return 2;
    } else if (ch == '3') {
        return 3;
    } else if (ch == '4') {
        return 4;
    } else if (ch == '5') {
        return 5;
    } else if (ch == '6') {
        return 6;
    } else if (ch == '7') {
        return 7;
    } else if (ch == '8') {
        return 8;
    } else if (ch == '9') {
        return 9;
    } else if (ch == 'a') {
        return 10;
    } else if (ch == 'b') {
        return 11;
    }
    return -1;
}

void drawMap() {
    mvprintw(5, 12, "0");
    mvprintw(6, 12, "1");
    mvprintw(7, 12, "2");
    mvprintw(4, 13, "6  7  8");
    mvprintw(8, 13, "9  a b");
    mvprintw(5, 18, "3");
    mvprintw(6, 18, "4");
    mvprintw(7, 18, "5");
}

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
    int threadStackPointer = 0;
    
    std::vector<pthread_t> carThreads;
    pthread_t lightThreads[12];
    Light *lights;
    lights = new Light[12];
    for (int i = 0; i < 12; ++i) {
        bool b;
        if (i < 6)
            b = true;
        else
            b = false;
        lights[i] = *new Light();
        lights[i].setNewTime(5);
        lights[i].setColor(b);
    }
    
    
    initscr();
    //raw();
    curs_set(0);
    
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    Crossroad *cros = new Crossroad(lights);
    
    pthread_mutex_lock(&mutex);
    cros->drawCrossroad();
    pthread_mutex_unlock(&mutex);
    
    for (int i = 0; i < 12; ++i) {
        pthread_create(&lightThreads[i], NULL, Light::light, &lights[i]);
    }
    
    carThreads.push_back(*new pthread_t());
    pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,'x','e',15,25,1,&carThreads.at(carThreads.size()-1),&mutex));
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
            pthread_mutex_lock(&mutex);
            for (int i = 0; i < 12; ++i) {
                if (lights[i].getCurrentState())
                    mvprintw(31+i, 0, "g");
                else
                    mvprintw(31+i, 0, "r");
            }
            pthread_mutex_unlock(&mutex);
            //continue;
            //refresh();
            //usleep(1000);
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
            //mvprintw(0, 0, "Zmiana mozliwych kierunkow dla drogi:");
            mvprintw(2, 0, "ustawienia drog - k");
            mvprintw(3, 0, "ustawienia swiatel - s");
            int ch = getch();
            while (ch != 'u') {
                ch = getch();
                if ( ch == 'r') {
                    cros->crashCount = 0;
                } else if ( ch == 'k') {
                    mvprintw(4, 0, "numer drogi");
                    drawMap();
                    ch = getch();
                    while (numFromChar(ch) == -1)
                        ch = getch();
                    int num = numFromChar(ch);
                    for (int i = 0; i < 4; ++i) {
                        int c = getch();
                        while ((c != 'n')&&(c != 's')&&(c != 'e')&&(c != 'w')) {
                            c = getch();
                        }
                        cros->roadsDirections[num][i] = c;
                        char cc = c;
                        mvprintw(10, i, &cc);
                    }
                } else if (ch == 's') {
                    //swiatla
                    mvprintw(4, 0, "numer swiatla");
                    drawMap();
                    ch = getch();
                    while (numFromChar(ch) == -1)
                        ch = getch();
                    int num = numFromChar(ch);

                    mvprintw(20, 0, "1  - 1, 2 - 2, 3 - 3, 4 - 4, 5 - 5");
                    int c = getch();
                    while ((c != '1')&&(c != '2')&&(c != '3')&&(c != '4')&&(c != '5')) {
                        c = getch();
                    }
                    int newLength;
                    if (ch == '1')
                        newLength = 1;
                    else if (ch == '2')
                        newLength = 2;
                    else if (ch == '3')
                        newLength = 3;
                    else if (ch == '4')
                        newLength = 4;
                    else
                        newLength = 5;
                    
                    lights[num].setNewTime(newLength);
                    
                    
                    
                }
            }
            cros->drawCrossroad();
            pthread_mutex_unlock(&mutex);
        }
        else if (ch == 'q') {
            break;
        }
        else {
            int x, y;
            char dest;
            randomCoords(y, x, dest);
            //pthread_mutex_lock(&mutex);
            int r = rand()%10 + 15;
            carThreads.push_back(*new pthread_t());
            pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,dest,dest,r,y,x,&carThreads.at(carThreads.size()-1),&mutex));
            //pthread_mutex_unlock(&mutex);
        }
    }
    
    for (int i = 0; i < carThreads.size(); ++i) {
        pthread_cancel(carThreads.at(i));
    }
    
    pthread_mutex_destroy(&mutex);
    endwin();
    
    delete cros;
    
    return 0;
}

