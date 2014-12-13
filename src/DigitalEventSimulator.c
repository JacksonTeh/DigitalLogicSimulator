#include <stdio.h>
#include <string.h>
#include "DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "InitNode.h"

Node *registerEvent(ModuleAndPin *moduleAndPin, Pipe *pipe, unsigned long long expiredPeriod)
{
    EventTime eventTime;
    Node *root = NULL, newTimeNode;

    storedEventTimeData(&eventTime, moduleAndPin, pipe);

    if(moduleAndPin != NULL)
        eventTime.time = expiredPeriod + determinePropagationDelay(moduleAndPin->module);
    else
        eventTime.time = expiredPeriod;

    genericResetNode(&newTimeNode, (void *)&eventTime);
    setNode(&newTimeNode, NULL, NULL, 'r');
    genericAddRedBlackTree(&root, &newTimeNode, compareEventTime);

    return root;
}

void storedEventTimeData(EventTime *eventTime, ModuleAndPin *moduleAndPin, Pipe *pipe)
{
    eventTime->moduleAndPin = moduleAndPin;
    eventTime->pipe = pipe;
}

unsigned long long determinePropagationDelay(Module *module)
{
    unsigned long long propagationDelay;

    if(!strcmp(module->name, "AND"))
        propagationDelay = 9 * ONE_NANO_SEC;
    else if(!strcmp(module->name, "OR"))
        propagationDelay = 14 * ONE_NANO_SEC;
    else if(!strcmp(module->name, "XOR"))
        propagationDelay = 10 * ONE_NANO_SEC;
    else if(!strcmp(module->name, "NAND"))
        propagationDelay = 9.5 * ONE_NANO_SEC;
    else if(!strcmp(module->name, "NOR"))
        propagationDelay = 10 * ONE_NANO_SEC;
    else if(!strcmp(module->name, "NOT"))
        propagationDelay = 9.5 * ONE_NANO_SEC;

    return propagationDelay;
}

int eventSimulator()
{
    
}