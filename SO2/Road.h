//
//  Road.h
//  SO2
//
//  Created by Tomasz on 28.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#ifndef __SO2__Road__
#define __SO2__Road__

#include <iostream>

class Road {
private:
    char streamDirection;
    int startCordY;
    int startCordX;
    int endCordY;
    int endCordX;
    char directionAuth;
    char destination;
public:
    Road(char,int,int,int,int,char,char);
};

#endif /* defined(__SO2__Road__) */
