#include <stdio.h>
#include "Rotations.h"

void leftRotate(Node **nodePtr)
{
    Node *tempNode1 = (*nodePtr)->right;
    Node *tempNode2 = tempNode1->left;

    tempNode1->left = *nodePtr;
    (*nodePtr)->right = tempNode2;

    *nodePtr = tempNode1;
}

void rightRotate(Node **nodePtr)
{
    Node *tempNode1 = (*nodePtr)->left;
    Node *tempNode2 = tempNode1->right;

    tempNode1->right = *nodePtr;
    (*nodePtr)->left = tempNode2;

    *nodePtr = tempNode1;
}

void leftRightRotate(Node **nodePtr)
{
    leftRotate(&((*nodePtr)->left));
    rightRotate(&(*nodePtr));
}

void rightLeftRotate(Node **nodePtr)
{
    rightRotate(&((*nodePtr)->right));
    leftRotate(&(*nodePtr));
}