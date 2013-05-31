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

int main(int argc, const char * argv[])
{

    // insert code here...
    //std::cout << "Hello, World!\n";
    
    initscr();
    raw();
    curs_set(0);
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    Car *newCar = new Car('s','w',15,25,0,&mutex);
    Car *anotherNewCar = new Car('x','e',10,25,150,&mutex);
    pthread_t *thread1 = new pthread_t();
    pthread_t *thread2 = new pthread_t();
    
    pthread_create(thread1, NULL, Car::move, newCar);
    pthread_create(thread2, NULL, Car::move, anotherNewCar);

    
    Crossroad *cros = new Crossroad();
    pthread_mutex_lock(&mutex);
    cros->drawCrossroad();
    pthread_mutex_unlock(&mutex);
    cros->doTraffic(*thread1);
    cros->doTraffic(*thread2);
    

    
    
    getch();
    
    endwin();
    
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    
    
    
    return 0;
}

