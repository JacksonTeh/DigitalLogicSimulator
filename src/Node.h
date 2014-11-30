#ifndef Node_H
#define Node_H

typedef struct Node Node;

struct Node
{
    Node *left;
    Node *right;
    char colour;    //'b' or 'r' or 'd' (black or red or double black)
    int data;
};

#endif // Node_H
