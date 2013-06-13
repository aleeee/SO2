//
//  Crossroad.cpp
//  SO2
//
//  Created by Tomasz on 25.05.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include "Crossroad.h"
#include "Car.h"
#include <ncurses.h>
#include <pthread.h>
#include <unistd.h>

Crossroad::Crossroad(Light *l) {
    xRange = 204;
    yRange = 63;
    roadsDirections = new int*[12];
    for (int i = 0; i < 12; ++i) {
        roadsDirections[i] = new int[4];
        roadsDirections[i][0] = 'n';
        roadsDirections[i][1] = 's';
        roadsDirections[i][2] = 'w';
        roadsDirections[i][3] = 'e';
    }
    crossRoadStructure = new int*[yRange];
    carsWithDirections = new int*[yRange];
    for (int i = 0; i < yRange; ++i) {
        crossRoadStructure[i] = new int[xRange];
        carsWithDirections[i] = new int[xRange];
        for (int j = 0; j < xRange; ++j) {
            crossRoadStructure[i][j] = ' ';
            carsWithDirections[i][j] = ' ';
        }
    }
    initStructureOfCrossroad();
    isStopped = 0;
    isQuited = 0;
    crashCount = 0;
    lights = l;
}

Crossroad::~Crossroad() {
    delete [] crossRoadStructure;
    delete [] carsWithDirections;
    delete [] roadsDirections;
}

void Crossroad::initStructureOfCrossroad() {
    int leftSide = 50;
    for (int i = 0; i < leftSide; ++i ) {
        crossRoadStructure[20][i] = '#';
    }
    for (int i = 0; i < leftSide; ++i) {
        crossRoadStructure[22][i]  = '-';
    }
    for (int i = 0; i < leftSide; ++i) {
        crossRoadStructure[24][i]  = '#';
    }
    for (int i = 0; i < leftSide; ++i) {
        crossRoadStructure[26][i]  = '-';
    }
    for (int i = 0; i < leftSide; ++i) {
        crossRoadStructure[28][i]  = '-';
    }
    for (int i = 0; i < leftSide; ++i) {
        crossRoadStructure[30][i]  = '#';
    }
    int rightSide = 70;
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[20][i] = '#';
    }
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[22][i] = '-';
    }
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[24][i] = '-';
    }
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[26][i] = '#';
    }
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[28][i] = '-';
    }
    for (int i = 203; i > rightSide; --i ) {
        crossRoadStructure[30][i] = '#';
    }
    int upperSide = 20;
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][50] = '#';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][54] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][58] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][62] = '#';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][66] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][70] = '#';
    }
    int downSide = 30;
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][50] = '#';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][54] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][58] = '#';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][62] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][66] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][70] = '#';
    }
    crossRoadStructure[upperSide][leftSide] = '#';
    crossRoadStructure[upperSide][rightSide] = '#';
    crossRoadStructure[downSide][rightSide] = '#';
    crossRoadStructure[downSide][leftSide] = '#';
}

void Crossroad::drawCrossroad() {
    mvprintw(0, 0, "Ilosc kolizji:");
    char *converter = new char[5];
    sprintf(converter, "%d", this->crashCount);
    mvprintw(0, 15, converter);
    for (int i = 0; i < yRange; ++i) {
        for (int j = 0; j < xRange; ++j) {
            if (crossRoadStructure[i][j] != ' ') {
                if (crossRoadStructure[i][j] == '#') {
                    mvprintw(i, j, "#");
                } else if (crossRoadStructure[i][j] == '-') {
                    mvprintw(i, j, "-");
                } else if (crossRoadStructure[i][j] == '|') {
                    mvprintw(i, j, "|");
                }
            }
        }
    }
}

bool Crossroad::check(char dest, int num) {
    for (int i = 0; i < 4; ++i) {
        if (roadsDirections[num][i] == dest) {
            return true;
        }
    }
    return false;
}

bool Crossroad::isAllowed(int y, int x, char dest) {
    if (x == 50) {
        if (y == 25) {
            return check(dest, 0);                         //  6 7 8
        } else if (y == 27) {                              // 0       3
            return check(dest, 1);                         // 1       4
        } else if (y == 29) {                              // 2       5
            return check(dest, 2);                         //  9 10 11
        }
    } else if (x == 70) {
        if (y == 21) {
            return check(dest, 3);
        } else if (y == 23) {
            return check(dest, 4);
        } else if (y == 25) {
            return check(dest, 5);
        }
    } else if (y == 20) {
        if (x == 52) {
            return check(dest, 6);
        } else if (x == 56) {
            return check(dest, 7);
        } else if (x == 60) {
            return check(dest, 8);
        }
    } else if (y == 30) {
        if (x == 60) {
            return check(dest, 9);
        } else if (x == 64) {
            return check(dest, 10);
        } else if (x == 68) {
            return check(dest, 11);
        }
    }
    
    return false;
}

bool Crossroad::isGreenLight(int y, int x) {
    if (x == 50) {
        if (y == 25) {
            return lights[0].getCurrentState();                       //  6 7 8
        } else if (y == 27) {                              // 0       3
            return lights[1].getCurrentState();                         // 1       4
        } else if (y == 29) {                              // 2       5
            return lights[2].getCurrentState();                        //  9 10 11
        }
    } else if (x == 70) {
        if (y == 21) {
            return lights[3].getCurrentState();
        } else if (y == 23) {
            return lights[4].getCurrentState();
        } else if (y == 25) {
            return lights[5].getCurrentState();
        }
    } else if (y == 20) {
        if (x == 52) {
            return lights[6].getCurrentState();
        } else if (x == 56) {
            return lights[7].getCurrentState();
        } else if (x == 60) {
            return lights[8].getCurrentState();
        }
    } else if (y == 30) {
        if (x == 60) {
            return lights[9].getCurrentState();
        } else if (x == 64) {
            return lights[10].getCurrentState();
        } else if (x == 68) {
            return lights[11].getCurrentState();
        }
    } 
    
    return true;
}