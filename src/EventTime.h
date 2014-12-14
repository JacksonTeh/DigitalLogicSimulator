#ifndef EventTime_H
#define EventTime_H

#include "DigitalSignalModule.h"

typedef struct EventTime EventTime;

struct EventTime
{
    unsigned long long time;
    Pipe *pipe;
    ModuleAndPin *moduleAndPin;
};

#endif // EventTime_H