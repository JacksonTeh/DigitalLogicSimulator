#ifndef InitNode_H
#define InitNode_H

#include "Node.h"
#include "DigitalSignalModule.h"

void setNode(Node *target, Node *left, Node *right, char colour);
void resetNode(Node *target, int data);

void setModuleAndPin(ModuleAndPin *target, ModuleAndPin *left, ModuleAndPin *right, char colour);
void resetModuleAndPin(ModuleAndPin *target);

#endif // InitNode_H