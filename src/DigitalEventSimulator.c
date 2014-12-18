#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "EventInfo.h"
#include "Node.h"

// Node *registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod)
void registerEvent(Node **eventRoot, ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod)
{
    EventInfo *eventInfo;
    Node *newEventNode;

    // eventInfo = createdEventInfo(moduleAndPin, pipe);
    newEventNode = createdNewEventNode(moduleAndPin, pipe);
    eventInfo = (EventInfo *)newEventNode->dataPtr;
    eventInfo->time = expiredPeriod;
    
    genericAddRedBlackTree(eventRoot, newEventNode, compareEventInfo);

    // assert(eventRoot != NULL);
    // assert(root->dataPtr != NULL);
    // return root;
}

// void storedEventInfoData(EventInfo *eventInfo, ModuleAndPin *moduleAndPin, Pipe *pipe)
// {
    // eventInfo->moduleAndPin = moduleAndPin;
    // eventInfo->pipe = pipe;
// }

int eventSimulator(Node *eventRoot)
{
    Node *removeNode;

    removeNode = findSmallestTimeEvent(&eventRoot);

    if(removeNode == NULL)
        return 1;

    EventInfo *eventInfo = (EventInfo *)removeNode->dataPtr;
    eventInfo->moduleAndPin->module->event(eventInfo->moduleAndPin, eventInfo->time);
    return 0;
}