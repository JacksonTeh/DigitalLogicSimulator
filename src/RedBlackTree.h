#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"

int compareModuleAndPin(void *rootPtr, void *newNode);
int compareEventInfo(void *rootPtr, void *newNode);

void genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*compareNode)(void *node, void *target));
Node *genericDelRedBlackTree(Node **rootPtr, Node *delNode, int (*compareNode)(void *node, void *target));

void addRedBlackTree(Node **rootPtr, Node *newNode);
Node *delRedBlackTree(Node **rootPtr, Node *delNode);
Node *_delRedBlackTree(Node **rootPtr, Node *delNode);
Node *delRedBlackTreeX(Node **rootPtr, Node *delNode);

void fixRootViolation(Node **rootPtr);
void fixChildViolation(Node **rootPtr);
void fixColourViolation(Node **rootPtr);
int isNodeRedColour(Node **rootPtr);

int isRed(Node *rootPtr);
int isBlack(Node *rootPtr);
int isDoubleBlack(Node *rootPtr, Node *removeNode);

void selectCases(Node **rootPtr, Node *removeNode);
int checkCases(Node *rootPtr);

void restructureRightBlackChildWithOneRedGrandchild(Node **rootPtr);
void restructureLeftBlackChildWithOneRedGrandchild(Node **rootPtr);
void restructureRightBlackChildWithBothBlackGrandchild(Node **rootPtr);
void restructureLeftBlackChildWithBothBlackGrandchild(Node **rootPtr);
void restructureRightRedChild(Node **rootPtr, Node *removeNode);
void restructureLeftRedChild(Node **rootPtr, Node *removeNode);

Node *removeNextLargerSuccessor(Node **parentPtr);

#endif // RedBlackTree_H
