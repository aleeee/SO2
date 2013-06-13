//
//  Light.h
//  SO2
//
//  Created by Tomasz on 13.06.2013.
//  Copyright (c) 2013 Tomasz. All rights reserved.
//

#ifndef __SO2__Light__
#define __SO2__Light__

#include <iostream>
#include <unistd.h>

class Light {
private:
    bool currentState;
    int untilSwitch;
public:
    Light();
    void setNewTime(int);
    void setColor(bool);
    bool getCurrentState();
    static void *light(void *ptr) {
        Light *l = reinterpret_cast<Light *>(ptr);
        
        while (true) {
            l->currentState = !l->currentState;
            sleep(l->untilSwitch);
        }
        
        return NULL;
    };    
};

#endif /* defined(__SO2__Light__) */
