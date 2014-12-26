#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "EventInfo.h"
#include "Node.h"

extern Node *eventRoot;

void registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod)
{
    EventInfo *eventInfo;
    Node *newEventNode;

    newEventNode = createdNewEventNode(moduleAndPin, pipe);
    eventInfo = (EventInfo *)newEventNode->dataPtr;
    eventInfo->time = expiredPeriod;

    genericAddRedBlackTree(&eventRoot, newEventNode, compareEventInfo);
}

int eventSimulator()
{
    Node *removeNode;

    removeNode = findSmallestTimeEvent(&eventRoot);

    if(removeNode == NULL)
        return 1;

    EventInfo *eventInfo = (EventInfo *)removeNode->dataPtr;

    if(eventInfo->pipe == NULL)
        eventInfo->moduleAndPin->module->event(eventInfo->moduleAndPin, eventInfo->time);
    else
        eventInfo->pipe->event(eventInfo->pipe, eventInfo->pipe->data, eventInfo->time);

    return 0;
}