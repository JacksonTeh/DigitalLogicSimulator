#include <stdio.h>
#include <malloc.h>
#include "Node.h"
#include "EventInfo.h"

Node *createdNewPipeDataNode(ModuleAndPin *moduleAndPin)
{
    Node *newNode;

    newNode = malloc(sizeof(Node));
    newNode->dataPtr = moduleAndPin;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->colour = 'r';

    return newNode;
}

Node *createdNewEventNode(ModuleAndPin *moduleAndPin, Pipe *pipe)
{
    Node *newNode;
    EventInfo *eventInfo = createdEventInfo(moduleAndPin, pipe);

    newNode = malloc(sizeof(Node));
    newNode->dataPtr = eventInfo;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->colour = 'r';

    return newNode;
}

void destroyEventNode(Node *node)
{
    if(node != NULL)
    {
        if(node->dataPtr != NULL)
            destroyEventInfo((EventInfo *)node->dataPtr);

        free(node);
    }
}

void destroyNode(Node *node)
{
    if(node != NULL)
        free(node);
}