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
    crossRoadStructure = new char*[yRange];
    for (int i = 0; i < yRange; ++i) {
        crossRoadStructure[i] = new char[xRange];
        for (int j = 0; j < xRange; ++j) {
            crossRoadStructure[i][j] = ' ';
        }
    }
    initStructureOfCrossroad();
    isStopped = 0;
    isQuited = 0;
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
    int rightSide = 75;
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
        crossRoadStructure[i][55] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][60] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][65] = '#';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][70] = '|';
    }
    for (int i = 0; i < upperSide; ++i) {
        crossRoadStructure[i][75] = '#';
    }
    int downSide = 30;
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][50] = '#';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][55] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][60] = '#';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][65] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][70] = '|';
    }
    for (int i = 62; i > downSide; --i) {
        crossRoadStructure[i][75] = '#';
    }
    crossRoadStructure[upperSide][leftSide] = '#';
    crossRoadStructure[upperSide][rightSide] = '#';
    crossRoadStructure[downSide][rightSide] = '#';
    crossRoadStructure[downSide][leftSide] = '#';
}

void Crossroad::drawCrossroad() {
    for (int i = 0; i < yRange; ++i) {
        for (int j = 0; j < xRange; ++j) {
            if (crossRoadStructure[i][j] != ' ') {
                mvprintw(i, j, &crossRoadStructure[i][j]);
            }
        }
    }
}
