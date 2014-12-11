#ifndef EventTime_H
#define EventTime_H

#include "DigitalSignalModule.h"

typedef struct EventTime EventTime;

struct EventTime
{
    // EventTime *left;
    // EventTime *right;
    // char colour;    //'b' or 'r' or 'd' (black or red or double black)
    unsigned long long time;
    // Module *module;
    Pipe *pipe;
    ModuleAndPin *moduleAndPin;
};

#endif // EventTime_H