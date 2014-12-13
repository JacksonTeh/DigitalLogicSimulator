#include "unity.h"
#include "DigitalEventSimulator.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "Rotations.h"
#include "InitNode.h"

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

void test_determinePropagationDelay_given_AND_module_should_return_9_point_5_ns(void)
{
    Module *AND;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_EQUAL(9 * ONE_NANO_SEC, determinePropagationDelay(AND));

    destroyModule(AND);
}

void test_determinePropagationDelay_given_OR_module_should_return_14_ns(void)
{
    Module *OR;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);

    TEST_ASSERT_EQUAL(14 * ONE_NANO_SEC, determinePropagationDelay(OR));

    destroyModule(OR);
}

void test_registerEvent_given_AND_module_and_pin_should_register_the_event_to_red_black_tree(void)
{
    Module *AND;
    ModuleAndPin moduleAndPin;
    EventTime *eventTime;
    Node *rootNode;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    storedModuleAndPin(&moduleAndPin, AND, AND->pin[0].pinNumber);

    rootNode = registerEvent(&moduleAndPin, NULL, ONE_NANO_SEC);
    eventTime = (EventTime *)rootNode->dataPtr;

    TEST_ASSERT_NOT_NULL(rootNode);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC + (9 * ONE_NANO_SEC), eventTime->time);
    TEST_ASSERT_EQUAL_PTR(NULL, eventTime->pipe);
    TEST_ASSERT_EQUAL_PTR(&moduleAndPin, eventTime->moduleAndPin);

    destroyModule(AND);
}

void test_registerEvent_given_pipe_should_register_the_event_to_red_black_tree(void)
{
	Pipe *pipe;
    EventTime *eventTime;
    Node *rootNode;

    pipe = createdPipeModule();

    rootNode = registerEvent(NULL, pipe, ONE_NANO_SEC);
    eventTime = (EventTime *)rootNode->dataPtr;

    TEST_ASSERT_NOT_NULL(rootNode);
    TEST_ASSERT_EQUAL_PTR(ONE_NANO_SEC, eventTime->time);
    TEST_ASSERT_EQUAL_PTR(pipe, eventTime->pipe);
    TEST_ASSERT_EQUAL_PTR(NULL, eventTime->moduleAndPin);
}

void test_eventSimulator_given_node_should_(void)
{

}