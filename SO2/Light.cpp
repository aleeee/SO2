//
//  Light.cpp
//  SO2
//
//  Created by Tomasz on 13.06.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#include "Light.h"

Light::Light() {
}

void Light::setNewTime(int time) {
    this->untilSwitch = time;
}

void Light::setColor(bool color) {
    this->currentState = color;
}

bool Light::getCurrentState() {
    bool b = this->currentState;
    return b;
}
