#include "unity.h"
#include "DigitalEventSimulator.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "Rotations.h"
#include "InitNode.h"
#include "CustomAssertions.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_storedEventTimeData_given_moduleAndPin_and_pipe_should_store_the_moduleAndPin_and_pipe(void)
{
    EventTime eventTime;
    Module *AND;
    ModuleAndPin moduleAndPin;
    Pipe *pipe;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);
    storedEventTimeData(&eventTime, &moduleAndPin, pipe);

    TEST_ASSERT_EQUAL_PTR(&moduleAndPin, eventTime.moduleAndPin);
    TEST_ASSERT_EQUAL_PTR(pipe, eventTime.pipe);

    destroyModule(AND);
    destroyPipe(pipe);
}
/*
void test_registerEvent_given_AND_module_and_pin_should_register_the_event_to_red_black_tree(void)
{
    Module *AND;
    ModuleAndPin moduleAndPin;
    // EventTime *eventTime;
    Node newNode, *root = NULL;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);
    // printf("moduleAndPin: %p\n", &moduleAndPin);

    genericAddRedBlackTree_Expect(&root, &newNode, compareEventTime);

    newNode = registerEvent(&moduleAndPin, NULL, ONE_NANO_SEC);
    // eventTime = (EventTime *)&rootNode->dataPtr;
    // printf("!moduleAndPin: %p\n", eventTime->moduleAndPin);
    // printf("!pipe: %p\n", eventTime->pipe);

    // TEST_ASSERT_NOT_NULL(rootNode);
    // TEST_ASSERT_NULL(rootNode->left);
    // TEST_ASSERT_NULL(rootNode->right);
    // TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventTime->time);
    // TEST_ASSERT_NULL(eventTime->pipe);
    // TEST_ASSERT_EQUAL_PTR(&moduleAndPin, eventTime->moduleAndPin);

    destroyModule(AND);
}

void xtest_registerEvent_given_pipe_should_register_the_event_to_red_black_tree(void)
{
	Pipe *pipe;
    EventTime *eventTime;
    Node *rootNode;

    pipe = createdPipeModule();

    // rootNode = registerEvent(NULL, pipe, ONE_NANO_SEC);
    eventTime = (EventTime *)rootNode->dataPtr;

    TEST_ASSERT_NOT_NULL(rootNode);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventTime->time);
    TEST_ASSERT_EQUAL_PTR(pipe, eventTime->pipe);
    TEST_ASSERT_EQUAL_PTR(NULL, eventTime->moduleAndPin);
} */

void test_eventSimulator_given_NULL_node_should_return_1(void)
{
    Node *root = NULL;

    TEST_ASSERT_EQUAL(1, eventSimulator(root));
}

void test_eventSimulator_given_node_contain_AND_module_and_pin_should_return_0_and_generate_event_for_AND(void)
{
    Node root;
    Module *AND;
    ModuleAndPin moduleAndPin;
    EventTime eventTime;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = HIGH;
    storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);
    storedEventTimeData(&eventTime, &moduleAndPin, NULL);
    genericSetNode(&root, (void *)&eventTime, NULL, NULL, 'r');

    TEST_ASSERT_EQUAL(0, eventSimulator(&root));
    TEST_ASSERT_EQUAL(HIGH, (AND->pin[8]).state);

    destroyModule(AND);
}