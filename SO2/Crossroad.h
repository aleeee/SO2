//
//  Crossroad.h
//  SO2
//
//  Created by Tomasz on 25.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#ifndef __SO2__Crossroad__
#define __SO2__Crossroad__

#include <iostream>
#include "Car.h"

class Crossroad {
private:
    char **crossRoadStructure;
    int xRange;// = 204;
    int yRange;// = 63;
public:
    Crossroad();
    void drawCrossroad();
    void initStructureOfCrossroad();
    void doTraffic(pthread_t);
};

#endif /* defined(__SO2__Crossroad__) */
