//
//  Road.cpp
//  SO2
//
//  Created by Tomasz on 28.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include "Road.h"

Road::Road(char sD, int sCY, int sCX, int eCY, int eCX, char dA, char d) {
    streamDirection = sD;
    startCordY = sCY;
    startCordX = sCX;
    endCordY = eCY;
    endCordX = eCX;
    directionAuth = dA;
    destination = d;
}
