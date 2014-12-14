#include <stdio.h>
#include "InitNode.h"

void setNode(Node *target, Node *left, Node *right, char colour)
{
    target->left = left;
    target->right = right;
    target->colour = colour;
}

void resetNode(Node *target, int data)
{
    target->left = NULL;
    target->right = NULL;
    target->colour = 'b';
    target->data = data;
}

void setEventTime(EventTime *time, long long data)
{
    time->time = data;
}

void genericResetNode(Node *target, void *data)
{
    target->left = NULL;
    target->right = NULL;
    target->colour = 'b';
    target->dataPtr = data;
}

void genericSetNode(Node *target, void *data, Node *left, Node *right, char colour)
{
    genericResetNode(target, data);
    setNode(target, left, right, colour);
}