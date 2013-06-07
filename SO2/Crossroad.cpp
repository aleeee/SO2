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

Crossroad::Crossroad() {
    xRange = 204;
    yRange = 63;
    crossRoadStructure = new int*[yRange];
    for (int i = 0; i < yRange; ++i) {
        crossRoadStructure[i] = new int[xRange];
        for (int j = 0; j < xRange; ++j) {
            crossRoadStructure[i][j] = ' ';
        }
    }
    initStructureOfCrossroad();
    isStopped = 0;
    isQuited = 0;
    crashCount = 0;
}

Crossroad::~Crossroad() {
    delete [] crossRoadStructure;
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
