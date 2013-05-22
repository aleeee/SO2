//
//  main.cpp
//  SO2
//
//  Created by Tomasz on 22.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include "ncurses.h"
#include "pthread.h"
#include <iostream>

using namespace std;

int main(int argc, const char * argv[])
{

    // insert code here...
    //std::cout << "Hello, World!\n";
    
    initscr();
    
    char c;
    cin >> c;
    
    endwin();
    
    return 0;
}

