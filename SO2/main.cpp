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
}

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
            y = 27;
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

int main(int argc, const char * argv[])
{
    srand(time(NULL));
    
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
            continue;
            refresh();
            usleep(1000);
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
        else if (ch == 'q') {
            break;
        }
        else {
            int x, y;
            char dest;
            randomCoords(y, x, dest);
            //pthread_mutex_lock(&mutex);
            carThreads.push_back(*new pthread_t());
            pthread_create(&carThreads.at(threadStackPointer++), NULL, Car::move, new Car(cros,dest,dest,25,y,x,&carThreads.at(carThreads.size()-1),&mutex));
            //pthread_mutex_unlock(&mutex);
        }
    }
    
    pthread_mutex_destroy(&mutex);
    //pthread_exit(0);
    endwin();
    
    delete cros;
    
    return 0;
}

