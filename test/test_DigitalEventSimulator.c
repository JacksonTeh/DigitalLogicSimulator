#include <assert.h>
#include "unity.h"
#include "DigitalEventSimulator.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "Rotations.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "EventInfo.h"
#include "Node.h"

void setUp(void)
{
}

void tearDown(void)
{
}

// void test_storedEventInfoData_given_moduleAndPin_and_pipe_should_store_the_moduleAndPin_and_pipe(void)
// {
    // EventInfo eventInfo;
    // Module *AND;
    // ModuleAndPin moduleAndPin;
    // Pipe *pipe;
    // int inputType = QUAD_2_INPUT;

    // AND = createdAndModule(inputType);
    // pipe = createdPipeModule();
    // storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);
    // storedEventInfoData(&eventInfo, &moduleAndPin, pipe);

    // TEST_ASSERT_EQUAL_PTR(&moduleAndPin, eventInfo.moduleAndPin);
    // TEST_ASSERT_EQUAL_PTR(pipe, eventInfo.pipe);

    // destroyModule(AND);
    // destroyPipe(pipe);
// }

void test_registerEvent_given_AND_module_and_pin_should_register_the_event_to_red_black_tree(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    EventInfo *eventInfo;
    Node *root = NULL;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);

    // genericAddRedBlackTree_Expect(&root, &newNode, compareEventInfo);

    // root = registerEvent(&moduleAndPin, NULL, ONE_NANO_SEC);
    registerEvent(&root, moduleAndPin, NULL, ONE_NANO_SEC);
    eventInfo = (EventInfo *)root->dataPtr;

    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_NULL(root->left);
    TEST_ASSERT_NULL(root->right);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventInfo->time);
    TEST_ASSERT_NULL(eventInfo->pipe);
    TEST_ASSERT_EQUAL_PTR(moduleAndPin, eventInfo->moduleAndPin);

    destroyModuleAndPin(moduleAndPin);
    destroyModule(AND);
    destroyEventNode(root);
}

void test_registerEvent_given_pipe_should_register_the_event_to_red_black_tree(void)
{
    Pipe *pipe;
    EventInfo *eventInfo;
    Node *root = NULL;
    int inputType = QUAD_2_INPUT;

    pipe = createdPipeModule();

    // genericAddRedBlackTree_Expect(&root, &newNode, compareEventInfo);

    // root = registerEvent(&moduleAndPin, NULL, ONE_NANO_SEC);
    registerEvent(&root, NULL, pipe, ONE_NANO_SEC);
    eventInfo = (EventInfo *)root->dataPtr;

    TEST_ASSERT_NOT_NULL(root);
    TEST_ASSERT_NULL(root->left);
    TEST_ASSERT_NULL(root->right);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventInfo->time);
    TEST_ASSERT_EQUAL_PTR(pipe, eventInfo->pipe);
    TEST_ASSERT_NULL(eventInfo->moduleAndPin);

    destroyEventNode(root);
}

void test_eventSimulator_given_NULL_node_should_return_1(void)
{
    Node *root = NULL;

    // removeNextLargerSuccessor_ExpectAndReturn(&root, newNode);

    TEST_ASSERT_EQUAL(1, eventSimulator(root));
}

void test_eventSimulator_given_node_contain_AND_module_and_pin_should_return_0_and_generate_event_for_AND(void)
{
    Node *root;
    Module *AND;
    ModuleAndPin *moduleAndPin;
    EventInfo eventInfo;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = HIGH;
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);
    root = createdNewEventNode(moduleAndPin, NULL);

    // removeNextLargerSuccessor_ExpectAndReturn(&rootPtr, newNode);

    TEST_ASSERT_EQUAL(0, eventSimulator(root));
    TEST_ASSERT_EQUAL(HIGH, (AND->pin[8]).state);

    destroyModuleAndPin(moduleAndPin);
    destroyModule(AND);
    destroyEventNode(root);
}