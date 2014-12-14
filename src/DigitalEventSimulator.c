#include <stdio.h>
#include <string.h>
#include "DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"

Node *registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod)
{
    EventTime eventTime;
    Node *root = NULL, newTimeNode;

    storedEventTimeData(&eventTime, moduleAndPin, pipe);

    // if(moduleAndPin != NULL)
        // eventTime.time = expiredPeriod + determinePropagationDelay(moduleAndPin->module);
    // else
    eventTime.time = expiredPeriod;

    // genericResetNode(newTimeNode, (void *)&eventTime);
    // setNode(newTimeNode, NULL, NULL, 'r');
    genericSetNode(&newTimeNode, (void *)&eventTime, NULL, NULL, 'r');
    genericAddRedBlackTree(&root, &newTimeNode, compareEventTime);

    return root;
}

void storedEventTimeData(EventTime *eventTime, ModuleAndPin *moduleAndPin, Pipe *pipe)
{
    eventTime->moduleAndPin = moduleAndPin;
    eventTime->pipe = pipe;
}

int eventSimulator(Node *rootPtr)
{
    Node *removeNode;

    removeNode = findSmallestTimeEvent(&rootPtr);

    if(removeNode == NULL)
        return 1;

    EventTime *eventTime = (EventTime *)removeNode->dataPtr;
    eventTime->moduleAndPin->module->event(eventTime->moduleAndPin, eventTime->time);
    return 0;
}