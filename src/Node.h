#ifndef Node_H
#define Node_H

// #include "DigitalSignalModule.h"
// #include "EventTime.h"

typedef struct Node Node;

// #include "EventTime.h"
#include "DigitalSignalModule.h"

struct Node
{
    Node *left;
    Node *right;
    char colour;    //'b' or 'r' or 'd' (black or red or double black)
    int data;
    void *dataPtr;
};

Node *createdNewPipeDataNode(ModuleAndPin *moduleAndPin);
Node *createdNewEventNode(ModuleAndPin *moduleAndPin, Pipe *pipe);
void destroyEventNode(Node *node);
void destroyNode(Node *node);

#endif // Node_H
