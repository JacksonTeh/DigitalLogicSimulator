#ifndef CustomAssertions_H
#define CustomAssertions_H

#include "Node.h"

#define TEST_ASSERT_EQUAL_NODE(left, right, colour, actualNode)              \
                    assertNode(left, right, colour, actualNode, __LINE__);

void assertNode(Node *left, Node *right, char colour, Node *actualNode, int lineNumber);

#endif // CustomAssertions_H