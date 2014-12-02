#ifndef RedBlackTree_H
#define RedBlackTree_H

#include "Node.h"
#include "DigitalSignalModule.h"

typedef enum {MODULE_AND_PIN, TIME_NODE} RBT_Type;

int compareModuleAndPin(void *moduleAndPin, void *targetModuleAndPin);

void genericAddRedBlackTree(void **rootNode, void *newNode, int typeOfRBT);
// void genericAddRedBlackTree(ModuleAndPin **rootPtr, ModuleAndPin *newModuleAndPin);
// Node *genericDelRedBlackTree(Node **rootPtr, Node *delNode);
// Node *_genericDelRedBlackTree(Node **rootPtr, Node *delNode);

Node *genericRemoveNextLargerSuccessor(Node **parentPtr);

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
