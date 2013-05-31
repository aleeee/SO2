//
//  Car.cpp
//  SO2
//
//  Created by Tomasz on 28.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include "Car.h"

Car::Car(char sy, char d, int sp, int yC, int xC, pthread_mutex_t *m) {
    symbol = sy;
    destination = d;
    speed = sp;
    yCord = yC;
    xCord = xC;
    mutex = m;
}


