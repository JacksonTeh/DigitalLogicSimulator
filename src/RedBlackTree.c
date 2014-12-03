#include <stdio.h>
#include "RedBlackTree.h"
#include "Rotations.h"
#include "ErrorCode.h"

void _genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*compareNode)(void *node, void *target));
Node *_genericDelRedBlackTree(Node **rootPtr, Node *delNode, int (*compareNode)(void *node, void *target));

int compareModuleAndPin(void *rootPtr, void *newNode)
{
    Node *root = (Node *)rootPtr;
    Node *new = (Node *)newNode;

    ModuleAndPin *rootNode = (ModuleAndPin *)root->dataPtr;
    ModuleAndPin *newModule = (ModuleAndPin *)new->dataPtr;

    if(rootNode == newModule)
        return -1;
    else if(rootNode > newModule)
        return 0;
    else if(rootNode < newModule)
        return 1;
}

int compareEventTime(void *rootPtr, void *newNode)
{
    Node *root = (Node *)rootPtr;
    Node *new = (Node *)newNode;

    EventTime *rootNode = (EventTime *)root->dataPtr;
    EventTime *newTime = (EventTime *)new->dataPtr;

    if(rootNode->time == newTime->time)
        return -1;
    else if(rootNode->time > newTime->time)
        return 0;
    else if(rootNode->time < newTime->time)
        return 1;
}

void genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*compareNode)(void *node, void *target))
{
    _genericAddRedBlackTree(rootPtr, newNode, compareNode);
    fixRootViolation(&(*rootPtr));
    (*rootPtr)->colour = 'b';
}

void _genericAddRedBlackTree(Node **rootPtr, Node *newNode, int (*compareNode)(void *node, void *target))
{
    Node *root = *rootPtr;

    if(root == NULL)
    {
        *rootPtr = newNode;
        return;
    }

    if(compareNode((void *)root, (void *)newNode) == -1)
        Throw(ERR_EQUIVALENT_NODE);
    else if(compareNode((void *)root, (void *)newNode) == 0)
    {
        _genericAddRedBlackTree(&root->left, newNode, compareNode);
        fixChildViolation(&root);
    }
    else if(compareNode((void *)root, (void *)newNode) == 1)
    {
        _genericAddRedBlackTree(&root->right, newNode, compareNode);
        fixChildViolation(&root);
    }

    if(root->left != NULL && root->right != NULL)
    {
        if(root->left->colour == 'r' && root->right->colour == 'r')     //indicate 4-nodes
            fixColourViolation(&root);
    }
}

Node *genericDelRedBlackTree(Node **rootPtr, Node *delNode, int (*compareNode)(void *node, void *target))
{
    Node *node = _genericDelRedBlackTree(rootPtr, delNode, compareNode);

    if((*rootPtr) != NULL)
        (*rootPtr)->colour = 'b';

    return node;
}

Node *_genericDelRedBlackTree(Node **rootPtr, Node *delNode, int (*compareNode)(void *node, void *target))
{
    Node *root = *rootPtr;
    Node *node, *successorNode;

    if(root == NULL)
        Throw(ERR_NODE_UNAVAILABLE);

    if(compareNode((void *)root, (void *)delNode) == -1)
    {
        if((*rootPtr)->right == NULL)
            successorNode = removeNextLargerSuccessor(&(*rootPtr)->left);
        else
            successorNode = removeNextLargerSuccessor(&(*rootPtr)->right);

        if(successorNode != root->right)
            successorNode->right = (*rootPtr)->right;

        if(successorNode != NULL)
        {
            successorNode->colour = (*rootPtr)->colour;
            *rootPtr = successorNode;
            (*rootPtr)->left = root->left;
            selectCases(&(*rootPtr), root);
        }
        else
            *rootPtr = NULL;

        return root;
    }
    else if(compareNode((void *)root, (void *)delNode) == 1)
        node = _genericDelRedBlackTree(&root->right, delNode, compareNode);
    else if(compareNode((void *)root, (void *)delNode) == 0)
        node = _genericDelRedBlackTree(&root->left, delNode, compareNode);

    selectCases(&(*rootPtr), node);

    return node;
}

void _addRedBlackTree(Node **rootPtr, Node *newNode);
Node *_delRedBlackTreeX(Node **rootPtr, Node *delNode);

/**
 *
 * Add node to Red Black Tree
 *
 */
void addRedBlackTree(Node **rootPtr, Node *newNode)
{
    _addRedBlackTree(rootPtr, newNode);
    fixRootViolation(&(*rootPtr));
    (*rootPtr)->colour = 'b';
}

void _addRedBlackTree(Node **rootPtr, Node *newNode)
{
    Node *root = *rootPtr;

    if(root == NULL)
    {
        *rootPtr = newNode;
        return;
    }

    if(newNode->data == root->data)
        Throw(ERR_EQUIVALENT_NODE);
    else if(newNode->data < root->data)
    {
        _addRedBlackTree(&root->left, newNode);
        fixChildViolation(&root);
    }
    else if(newNode->data > root->data)
    {
        _addRedBlackTree(&root->right, newNode);
        fixChildViolation(&root);
    }

    if(root->left != NULL && root->right != NULL)
    {
        if(root->left->colour == 'r' && root->right->colour == 'r')     //indicate 4-nodes
            fixColourViolation(&root);
    }
}

void fixRootViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left != NULL)
    {
        if(root->left->colour == 'r')
        {
            if(root->left->left != NULL)
            {
                if(!isNodeRedColour(&root->left))
                    return;
                else
                    rightRotate(&(*rootPtr));
            }
            else
            {
                if(!isNodeRedColour(&root->left))
                    return;
                else
                    leftRightRotate(&(*rootPtr));
            }

            (*rootPtr)->right->colour = 'r';
        }
    }
    else if(root->right != NULL)
    {
        if(root->right->colour == 'r')
        {
            if(root->right->right != NULL)
            {
                if(!isNodeRedColour(&root->right))
                    return;
                else
                    leftRotate(&(*rootPtr));
            }
            else
            {
                if(!isNodeRedColour(&root->right))
                    return;
                else
                    rightLeftRotate(&(*rootPtr));
            }

            (*rootPtr)->left->colour = 'r';
        }
    }
}

void fixChildViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->colour == 'r')
    {
        if(root->left != NULL)
        {
            if(!isNodeRedColour(&root->left))
                return;
            else
                rightRotate(&root);
        }
        else
        {
            if(!isNodeRedColour(&root->right))
                return;
            else
                leftRotate(&root);
        }
    }
}

void fixColourViolation(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left->left != NULL || root->left->right != NULL || root->right->left != NULL || root->right->right != NULL)
    {
        root->left->colour = 'b';
        root->right->colour = 'b';
        root->colour = 'r';
    }
}

int isNodeRedColour(Node **rootPtr)
{
    Node *root = *rootPtr;

    if(root->left != NULL)
    {
        if(root->left->colour == 'r')
            return 1;
    }
    else if(root->right != NULL)
    {
        if(root->right->colour == 'r')
            return 1;
    }

    return 0;
}

/**
 *
 * Delete node from Red Black Tree
 *
 */
Node *delRedBlackTree(Node **rootPtr, Node *delNode)
{
    Node *node = _delRedBlackTree(rootPtr, delNode);

    if((*rootPtr) != NULL)
        (*rootPtr)->colour = 'b';

    return node;
}

Node *_delRedBlackTree(Node **rootPtr, Node *delNode)
{
    Node *root = *rootPtr;
    Node *node, *successorNode;

    if(root == NULL)
        Throw(ERR_NODE_UNAVAILABLE);

    if(root->data == delNode->data)
    {
        if((*rootPtr)->right == NULL)
            successorNode = removeNextLargerSuccessor(&(*rootPtr)->left);
        else
            successorNode = removeNextLargerSuccessor(&(*rootPtr)->right);

        if(successorNode != root->right)
            successorNode->right = (*rootPtr)->right;

        if(successorNode != NULL)
        {
            successorNode->colour = (*rootPtr)->colour;
            *rootPtr = successorNode;
            (*rootPtr)->left = root->left;
            selectCases(&(*rootPtr), root);
        }
        else
            *rootPtr = NULL;

        return root;
    }
    else if(root->data < delNode->data)
        node = _delRedBlackTree(&root->right, delNode);
    else if(root->data > delNode->data)
        node = _delRedBlackTree(&root->left, delNode);

    selectCases(&(*rootPtr), node);

    return node;
}

int isRed(Node *rootPtr)
{
    if(rootPtr != NULL)
    {
        if(rootPtr->colour == 'r')
            return 1;
    }

    return 0;
}

int isBlack(Node *rootPtr)
{
    if(rootPtr == NULL || rootPtr->colour == 'b')
        return 1;
    else
        return 0;
}

/**
* Note: x == not possible
*	node          removed node        return
*	-----------------------------------------
*	NULL            NULL                x
*	NULL            red                 0
*	NULL            black               1
*	NULL            double black        x
*	red             NULL                x
*	red             red                 0
*	red             black               0
*	red             double black        x
*	black           NULL                x
*	black           red                 0
*	black           black               0
*	black           double black        x
*	double black    NULL                x
*	double black    red                 1
*	double black    black               1
*	double black    double black        x
*/
int isDoubleBlack(Node *rootPtr, Node *removeNode)
{
    if(rootPtr == NULL && removeNode->colour == 'r')
        return 0;
    else if((rootPtr == NULL && removeNode->colour == 'b') ||
            (rootPtr->colour == 'd' && (removeNode->colour == 'b' || removeNode->colour == 'r')))
        return 1;
    else
        return 0;
}

void selectCases(Node **rootPtr, Node *removeNode)
{
    if((*rootPtr)->left != NULL || (*rootPtr)->right != NULL)
    {
        if(isDoubleBlack((*rootPtr)->left, removeNode))           //left side case
        {
            if(checkCases((*rootPtr)->right) == 1)
                restructureRightBlackChildWithOneRedGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->right) == 2)
                restructureRightBlackChildWithBothBlackGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->right) == 3)
                restructureRightRedChild(&(*rootPtr), removeNode);
        }
        else if(isDoubleBlack((*rootPtr)->right, removeNode))     //right side case
        {
            if(checkCases((*rootPtr)->left) == 1)
                restructureLeftBlackChildWithOneRedGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->left) == 2)
                restructureLeftBlackChildWithBothBlackGrandchild(&(*rootPtr));
            else if(checkCases((*rootPtr)->left) == 3)
                restructureLeftRedChild(&(*rootPtr), removeNode);
                // printf("yes\n");
        }
    }
}

/**
 * To check which cases should be for the RBT
 *
 * Input:
 *      rootPtr     is pointer to Node
 *
 * Return
 *      1           indicate case: (1a) The sibling is black and it has a red nephew
                                   (1b) The sibling is black and it has a red nephew
 *      2           indicate case: (2a) The sibling is black and both nephew are black
                                   (2b) The sibling is black and both nephew are black
 *      3           indicate case: (3) The sibling is red
 */
int checkCases(Node *rootPtr)
{
    if(isBlack(rootPtr) && (isRed(rootPtr->left) || isRed(rootPtr->right)))             //case 1
        return 1;
    else if(isBlack(rootPtr) && (isBlack(rootPtr->left) || isBlack(rootPtr->right)))    //case 2
        return 2;
    else if(isRed(rootPtr))                                                             //case 3
    {
        if(rootPtr->left == NULL && rootPtr->right == NULL)
            return 0;

        return 3;
    }
}

//case 1
void restructureRightBlackChildWithOneRedGrandchild(Node **rootPtr)
{
    Node *rightChild = (*rootPtr)->right;

    if(isRed(rightChild->right))
        leftRotate(&(*rootPtr));
    else if(isRed(rightChild->left))
        rightLeftRotate(&(*rootPtr));

    (*rootPtr)->colour = (*rootPtr)->left->colour;
    (*rootPtr)->left->colour = 'b';
    (*rootPtr)->right->colour = 'b';
}

//case 1
void restructureLeftBlackChildWithOneRedGrandchild(Node **rootPtr)
{
    Node *leftChild = (*rootPtr)->left;

    if(isRed(leftChild->left))
        rightRotate(&(*rootPtr));
    else if(isRed(leftChild->right))
        leftRightRotate(&(*rootPtr));

    (*rootPtr)->colour = (*rootPtr)->right->colour;
    (*rootPtr)->left->colour = 'b';
    (*rootPtr)->right->colour = 'b';
}

//case 2
void restructureRightBlackChildWithBothBlackGrandchild(Node **rootPtr)
{
    if((*rootPtr)->colour == 'r')
        (*rootPtr)->colour = 'b';
    else
        (*rootPtr)->colour = 'd';

    (*rootPtr)->right->colour = 'r';

    if((*rootPtr)->left != NULL)
        (*rootPtr)->left->colour = 'b';
}

//case 2
void restructureLeftBlackChildWithBothBlackGrandchild(Node **rootPtr)
{
    if((*rootPtr)->colour == 'r')
        (*rootPtr)->colour = 'b';
    else
        (*rootPtr)->colour = 'd';

    (*rootPtr)->left->colour = 'r';

    if((*rootPtr)->right != NULL)
        (*rootPtr)->right->colour = 'b';
}

//case 3
void restructureRightRedChild(Node **rootPtr, Node *removeNode)
{
    leftRotate(&(*rootPtr));

    (*rootPtr)->left->colour = 'r';
    (*rootPtr)->colour = 'b';

    // if(isDoubleBlack((*rootPtr)->left->left, removeNode))
    // {
        // if(checkCases((*rootPtr)->left->right) == 1)
            // restructureRightBlackChildWithOneRedGrandchild(&(*rootPtr)->left);
        // else if(checkCases((*rootPtr)->left->right) == 2)
            // restructureRightBlackChildWithBothBlackGrandchild(&(*rootPtr)->left);
    // }
    selectCases(&(*rootPtr)->left, removeNode);
}

//case 3
void restructureLeftRedChild(Node **rootPtr, Node *removeNode)
{
    rightRotate(&(*rootPtr));

    (*rootPtr)->right->colour = 'r';
    (*rootPtr)->colour = 'b';

    selectCases(&(*rootPtr)->right, removeNode);
}

/**
 *
 * Remove the next larger successor node from Red Black Tree
 *
 */
Node *removeNextLargerSuccessor(Node **parentPtr)
{
    Node *removeNode;

    if(*parentPtr == NULL)
        return NULL;

    if((*parentPtr)->left == NULL && (*parentPtr)->right == NULL)
    {
        removeNode = *parentPtr;
        *parentPtr = NULL;
        return removeNode;
    }
    else
    {
        if((*parentPtr)->left != NULL)
            removeNode = removeNextLargerSuccessor(&(*parentPtr)->left);
        else
        {
            removeNode = *parentPtr;
            *parentPtr = (*parentPtr)->right;
            (*parentPtr)->colour = 'b';
        }
    }

    selectCases(&(*parentPtr), removeNode);

    return removeNode;
}

////////////////////////////////////////////////////
//                                                //
//           Old delete node code                 //
//                                                //
////////////////////////////////////////////////////
Node *delRedBlackTreeX(Node **rootPtr, Node *delNode)
{
    Node *node = _delRedBlackTree(rootPtr, delNode);

    if((*rootPtr) != NULL)
        (*rootPtr)->colour = 'b';

    return node;
}

Node *_delRedBlackTreeX(Node **rootPtr, Node *delNode)
{
    Node *root = *rootPtr;
    Node *node;

    if(root == NULL)
        Throw(ERR_NODE_UNAVAILABLE);

    if(root->data == delNode->data)
    {
        *rootPtr = NULL;
        return root;
    }
    else if(root->data < delNode->data)
        node = _delRedBlackTree(&root->right, delNode);
    else if(root->data > delNode->data)
        node = _delRedBlackTree(&root->left, delNode);

    if(root != NULL)
    {
        if(root->left == NULL && root->right != NULL)
        {
            if(root->right->left != NULL || root->right->right != NULL)
            {
                leftRotate(&(*rootPtr));
                (*rootPtr)->left->right->colour = 'r';
            }

            if(root->colour == 'r')
            {
                // printf("yes\n");
                if(root->left != NULL)
                    (*rootPtr)->left->colour = 'r';
                else if(root->right != NULL)
                    (*rootPtr)->right->colour = 'r';

                (*rootPtr)->colour = 'b';
            }
        }
        else if(root->left != NULL && root->right == NULL)
        {
            if(root->left->left != NULL || root->left->right != NULL)
            {
                rightRotate(&(*rootPtr));
                (*rootPtr)->right->left->colour = 'r';
            }

            if(root->colour == 'r')
            {
                if(root->left != NULL)
                    (*rootPtr)->left->colour = 'r';
                else if(root->right != NULL)
                    (*rootPtr)->right->colour = 'r';

                (*rootPtr)->colour = 'b';
            }
        }
    }

    return node;
}