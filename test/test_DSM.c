#include <malloc.h>
#include <stdio.h>
#include "unity.h"
#include "Node.h"
#include "EventInfo.h"
#include "DigitalSignalModule.h"
#include "InitNode.h"
#include "CException.h"
#include "mock_DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "Rotations.h"
#include "EventInfo.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createdModuleAndPin_given_AND_module_and_its_pin_should_return_moduleAndPin(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    moduleAndPin = createdModuleAndPin(AND, AND->pin[0].pinNumber);

    TEST_ASSERT_EQUAL_PTR(AND, moduleAndPin->module);
    TEST_ASSERT_EQUAL_PTR(&AND->pin[0], moduleAndPin->pin);
 
    destroyModuleAndPin(moduleAndPin);
}

void xtest_configureInputOutput_given_invalid_output_pin_for_OR_module_should_throw_ERR_NOT_OUT_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND, *OR;

    int inputType = QUAD_2_INPUT;

    Try{
        OR = createdOrModule(inputType);
        AND = createdAndModule(inputType);
        OR->configure((void *)OR, (void *)&OR->pin[1], (void *)AND, (void *)&AND->pin[0]);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_NOT_OUT_PIN.");
    } Catch(err) {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_OUT_PIN, err, "Expected ERR_NOT_OUT_PIN exception");
    }

    destroyModule(AND);
    destroyModule(OR);
}

void xtest_configureInputOutput_given_invalid_input_pin_for_AND_module_should_throw_ERR_NOT_IN_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND, *OR;

    int inputType = QUAD_2_INPUT;

    Try{
        OR = createdOrModule(inputType);
        AND = createdAndModule(inputType);
        OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[9]);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_NOT_IN_PIN.");
    } Catch(err) {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_IN_PIN, err, "Expected ERR_NOT_IN_PIN exception");
    }

    destroyModule(AND);
    destroyModule(OR);
}

void test_configureInputOutput_given_AND_and_OR_should_connect_output_from_OR_to_a_pipe_module(void)
{
    Module *AND, *OR;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    AND = createdAndModule(inputType);

    OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[0]);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_NOT_NULL((OR->pin[9]).pipe);

    destroyModule(AND);
    destroyModule(OR);
}

void test_configureInputOutput_given_AND_and_OR_that_connected_to_pipe_should_connect_output_from_pipe_to_AND_module_and_add_data_to_pipe(void)
{
    Module *AND, *OR;
    Pipe *pipe;
    ModuleAndPin *moduleAndPin;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    (OR->pin[9]).pipe = pipe;

    // genericAddRedBlackTree_Expect(&((OR->pin[9]).pipe)->data, &newNode, compareModuleAndPin);

    OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[0]);
    moduleAndPin = (OR->pin[9]).pipe->data->dataPtr;

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_NOT_NULL((OR->pin[9]).pipe);
    TEST_ASSERT_EQUAL_PTR((OR->pin[9]).pipe, (AND->pin[0]).pipe);
    TEST_ASSERT_EQUAL_PTR(AND, moduleAndPin->module);
    TEST_ASSERT_EQUAL_PTR(&AND->pin[0], moduleAndPin->pin);

    destroyModule(AND);
    destroyModule(OR);
}
