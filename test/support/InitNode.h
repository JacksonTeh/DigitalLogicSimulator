#ifndef InitNode_H
#define InitNode_H

#include "Node.h"
#include "DigitalSignalModule.h"
#include "EventTime.h"

void setNode(Node *target, Node *left, Node *right, char colour);
void resetNode(Node *target, int data);

void setEventTime(EventTime *time, long long data);

void genericResetNode(Node *target, void *data);
void genericSetNode(Node *target, void *data, Node *left, Node *right, char colour);

#endif // InitNode_H