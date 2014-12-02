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

void setModuleAndPin(ModuleAndPin *target, ModuleAndPin *left, ModuleAndPin *right, char colour)
{
    target->left = left;
    target->right = right;
    target->colour = colour;
}

void resetModuleAndPin(ModuleAndPin *target)
{
    target->left = NULL;
    target->right = NULL;
    target->colour = 'b';
    target->module = NULL;
    target->pin = NULL;
}