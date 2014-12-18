#ifndef EventInfo_H
#define EventInfo_H

typedef struct EventInfo EventInfo;

#include "DigitalSignalModule.h"

struct EventInfo
{
    unsigned long long time;
    Pipe *pipe;
    ModuleAndPin *moduleAndPin;
};

EventInfo *createdEventInfo(ModuleAndPin *moduleAndPin, Pipe *pipe);
void destroyEventInfo(EventInfo *eventInfo);

#endif // EventInfo_H