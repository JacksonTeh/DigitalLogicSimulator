#include <malloc.h>
#include "EventInfo.h"

EventInfo *createdEventInfo(ModuleAndPin *moduleAndPin, Pipe *pipe)
{
    EventInfo *eventInfo;

    eventInfo = malloc(sizeof(EventInfo));
    eventInfo->moduleAndPin = moduleAndPin;
    eventInfo->pipe = pipe;
}

void destroyEventInfo(EventInfo *eventInfo)
{
    if(eventInfo != NULL)
        free(eventInfo);
}
