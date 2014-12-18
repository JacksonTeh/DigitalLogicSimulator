#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "EventInfo.h"
#include "DigitalSignalModule.h"
#include "DigitalEventSimulator.h"
#include "InitNode.h"
#include "RedBlackTree.h"
#include "Rotations.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createdNewEventNode_given_moduleAndPin_and_pipe_should_store_in_Node_and_return_it(void)
{
    Node *newNode;
    Module *AND;
    ModuleAndPin moduleAndPin;
    EventInfo eventInfo, *result;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);

    newNode = createdNewEventNode(&moduleAndPin, NULL);
    result = (EventInfo *)newNode->dataPtr;

    TEST_ASSERT_NOT_NULL(newNode);
    TEST_ASSERT_NULL(newNode->left);
    TEST_ASSERT_NULL(newNode->right);
    TEST_ASSERT_EQUAL('r', newNode->colour);
    TEST_ASSERT_EQUAL_PTR(&moduleAndPin, result->moduleAndPin);
    TEST_ASSERT_EQUAL_PTR(NULL, result->pipe);

    destroyEventNode(newNode);
}
