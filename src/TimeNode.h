#ifndef TimeNode_H
#define TimeNode_H

typedef struct TimeNode TimeNode;

struct TimeNode
{
    TimeNode *left;
    TimeNode *right;
    char colour;    //'b' or 'r' or 'd' (black or red or double black)
    long long time;
};

#endif // TimeNode_H