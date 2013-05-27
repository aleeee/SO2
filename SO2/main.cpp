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
#include "Crossroad.h"

int main(int argc, const char * argv[])
{

    // insert code here...
    //std::cout << "Hello, World!\n";
    
    initscr();
    curs_set(0);
    
    Crossroad *cros = new Crossroad();
    cros->drawCrossroad();
    

    
    getch();
    
    
    endwin();
    
    return 0;
}

