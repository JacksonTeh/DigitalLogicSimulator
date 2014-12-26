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

extern Node *eventRoot;

void setUp(void)
{
    eventRoot = NULL;
}

void tearDown(void)
{
}

void test_registerEvent_given_AND_module_and_pin_should_register_the_event_to_red_black_tree(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    EventInfo *eventInfo;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);

    registerEvent(moduleAndPin, NULL, ONE_NANO_SEC);
    eventInfo = (EventInfo *)eventRoot->dataPtr;

    TEST_ASSERT_NOT_NULL(eventRoot);
    TEST_ASSERT_NULL(eventRoot->left);
    TEST_ASSERT_NULL(eventRoot->right);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventInfo->time);
    TEST_ASSERT_NULL(eventInfo->pipe);
    TEST_ASSERT_EQUAL_PTR(moduleAndPin, eventInfo->moduleAndPin);

    destroyModuleAndPin(moduleAndPin);
    destroyModule(AND);
    destroyEventNode(eventRoot);
}

void test_registerEvent_given_pipe_should_register_the_event_to_red_black_tree(void)
{
    Pipe *pipe;
    EventInfo *eventInfo;
    int inputType = QUAD_2_INPUT;

    pipe = createdPipeModule();

    registerEvent(NULL, pipe, ONE_NANO_SEC);
    eventInfo = (EventInfo *)eventRoot->dataPtr;

    TEST_ASSERT_NOT_NULL(eventRoot);
    TEST_ASSERT_NULL(eventRoot->left);
    TEST_ASSERT_NULL(eventRoot->right);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventInfo->time);
    TEST_ASSERT_EQUAL_PTR(pipe, eventInfo->pipe);
    TEST_ASSERT_NULL(eventInfo->moduleAndPin);

    destroyEventNode(eventRoot);
}

void test_eventSimulator_given_NULL_node_should_return_1(void)
{
    TEST_ASSERT_EQUAL(1, eventSimulator());
}

void test_eventSimulator_given_node_contain_AND_module_and_pin_should_return_0_and_generate_event_for_AND(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = HIGH;
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);
    eventRoot = createdNewEventNode(moduleAndPin, NULL);

    TEST_ASSERT_EQUAL(0, eventSimulator());
    TEST_ASSERT_EQUAL(HIGH, (AND->pin[8]).state);
    TEST_ASSERT_NULL(eventRoot);

    destroyModuleAndPin(moduleAndPin);
    destroyModule(AND);
    destroyEventNode(eventRoot);
}

void test_eventSimulator_given_node_contain_pipe_module_with_pipe_data_should_return_0_and_generate_event_for_pipe(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    Pipe *pipe;
    Node *newNode;
    EventInfo *eventInfo, *result;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[1]).state = HIGH;
    pipe = createdPipeModule();
    pipe->stateToFire = HIGH;
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);
    newNode = createdNewPipeDataNode(moduleAndPin);
    genericSetNode(newNode, (void *)moduleAndPin, NULL, NULL, 'r');
    pipe->data = newNode;
    eventRoot = createdNewEventNode(NULL, pipe);
    eventInfo = (EventInfo *)eventRoot->dataPtr;
    eventInfo->time = ONE_NANO_SEC;

    TEST_ASSERT_EQUAL(0, eventSimulator());

    result = (EventInfo *)eventRoot->dataPtr;

    TEST_ASSERT_NOT_NULL(eventRoot);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_NULL(result->pipe);
    TEST_ASSERT_EQUAL_PTR(AND, result->moduleAndPin->module);
    TEST_ASSERT_EQUAL_PTR(&AND->pin[0], result->moduleAndPin->pin);
    TEST_ASSERT_EQUAL(ONE_NANO_SEC + AND_PROPAGATION_DELAY, result->time);

    destroyPipeData(pipe);
    destroyModule(AND);
    destroyEventNode(eventRoot);
}