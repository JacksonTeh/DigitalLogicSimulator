#ifndef CustomAssertions_H
#define CustomAssertions_H

#include "Node.h"
#include "DigitalSignalModule.h"

#define TEST_ASSERT_EQUAL_NODE(left, right, colour, actualNode)              \
                    assertNode(left, right, colour, actualNode, __LINE__);

#define TEST_ASSERT_EQUAL_MODULE_AND_PIN(left, right, colour, actualModuleAndPin)       \
                    assertModuleAndPin(left, right, colour, actualModuleAndPin, __LINE__);

void assertNode(Node *left, Node *right, char colour, Node *actualNode, int lineNumber);
void assertModuleAndPin(ModuleAndPin *left, ModuleAndPin *right, char colour, ModuleAndPin *actualModuleAndPin, int lineNumber);

#endif // CustomAssertions_H