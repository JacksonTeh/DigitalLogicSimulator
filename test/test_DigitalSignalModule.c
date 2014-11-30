#include <malloc.h>
#include <stdio.h>
#include "unity.h"
#include "DigitalSignalModule.h"
#include "CException.h"
#include "mock_DigitalEventSimulator.h"
#include "mock_GenericRedBlackTree.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_determineNumOfInputPin_given_QUAD_2_INPUT_type_should_return_8(void)
{
    TEST_ASSERT_EQUAL(8, determineNumOfInputPin(QUAD_2_INPUT));
}

void test_determineNumOfInputPin_given_TRI_3_INPUT_type_should_return_9(void)
{
    TEST_ASSERT_EQUAL(9, determineNumOfInputPin(TRI_3_INPUT));
}

void test_determineNumOfInputPin_given_HEX_INV_type_should_return_6(void)
{
    TEST_ASSERT_EQUAL(6, determineNumOfInputPin(HEX_INV));
}

void test_determineNumOfOutputPin_given_QUAD_2_INPUT_type_should_return_4(void)
{
    TEST_ASSERT_EQUAL(4, determineNumOfOutputPin(QUAD_2_INPUT));
}

void test_determineNumOfOutputPin_given_TRI_3_INPUT_type_should_return_3(void)
{
    TEST_ASSERT_EQUAL(3, determineNumOfOutputPin(TRI_3_INPUT));
}

void test_determineNumOfOutputPin_given_DUAL_4_INPUT_type_should_return_2(void)
{
    TEST_ASSERT_EQUAL(2, determineNumOfOutputPin(DUAL_4_INPUT));
}

void test_determineNumOfOutputPin_given_HEX_INV_type_should_return_6(void)
{
    TEST_ASSERT_EQUAL(6, determineNumOfOutputPin(HEX_INV));
}

void test_createdAndModule_given_HEX_INV_type_should_thrown_ERR_INVALID_INPUT_TYPE(void)
{
    CEXCEPTION_T err;
    Module *AND;
    int inputType = HEX_INV;

    Try{
        AND = createdAndModule(inputType);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_INVALID_INPUT_TYPE.");
    } Catch(err){
        TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_INPUT_TYPE, err, "Expected ERR_INVALID_INPUT_TYPE exception");
        printf("Success: Exception generated. Error code: %d.\n", err);
    }
}

void test_createdAndModule_given_QUAD_2_INPUT_type_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int i, inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL_PTR(TOTAL_PIN, AND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        // TEST_ASSERT_EQUAL_PTR(NULL, (AND->pin[i]).moduleConnected);
        TEST_ASSERT_EQUAL_PTR(NULL, (AND->pin[i]).pipe);
    }
	// printf("yes\n");
    destroyModule(AND);
}

void test_createdAndModule_given_TRI_3_INPUT_type_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int i, inputType = TRI_3_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL_PTR(TOTAL_PIN, AND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL_PTR(NULL, (AND->pin[i]).pipe);
    }

    destroyModule(AND);
}

void test_createdAndModule_given_DUAL_4_INPUT_type_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int i, inputType = DUAL_4_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL_PTR(TOTAL_PIN, AND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 7 && i < 10)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL_PTR(NULL, (AND->pin[i]).pipe);
    }

    destroyModule(AND);
}

void test_createdPipeModule_should_create_module_for_pipe(void)
{
    Pipe *pipe;
    Module *module;

    pipe = createdPipeModule();
    // module = pipe->moduleAndPin->module;

    TEST_ASSERT_NOT_NULL(pipe);
    TEST_ASSERT_EQUAL_PTR(&pipeEvent, pipe->event);
    TEST_ASSERT_EQUAL_PTR(&setPipe, pipe->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, pipe->configure);
    // TEST_ASSERT_EQUAL_PTR(NULL, module);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->module);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->pin);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->left);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->right);
    TEST_ASSERT_EQUAL_PTR(UNKNOWN, pipe->stateToFire);

    destroyPipe(pipe);
}

void test_pipeAttach_should_attach_pipe_module_to_AND_module(void)
{
    Pipe *pipe;
    Module *AND;
    int inputType = QUAD_2_INPUT, andInPin = 1;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();

    // printf("pipe: %p\n", pipe);
    // printf("pipe->moduleAndPin: %p\n", pipe->moduleAndPin);
    // printf("pipe->moduleAndPin->module: %p\n", pipe->moduleAndPin->module);
    printf("pipe->moduleAndPin->pin: %p\n", pipe->moduleAndPin->pin);
    printf("AND: %p\n", AND);
    printf("AND->pin[andInPin-1]: %p\n", AND->pin[andInPin-1]);
    pipeAttach(&pipe, AND, &andInPin);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(pipe);
    TEST_ASSERT_EQUAL_PTR(AND, pipe->moduleAndPin->module);
    TEST_ASSERT_EQUAL_PTR(&AND->pin[andInPin-1], pipe->moduleAndPin->pin);

    destroyPipe(pipe);
    destroyModule(AND);
}

void xtest_configureInputOutput_given_invalid_output_pin_should_throw_ERR_NOT_OUTPUT_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND, *OR;

    int inputType = QUAD_2_INPUT, orOutPin = 2, andInPin = 1;

    Try{
        OR = createdOrModule(inputType);
        AND = createdAndModule(inputType);
        OR->configure((void *)OR, (void *)orOutPin, (void *)AND, (void *)andInPin);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_NOT_OUT_PIN.");
    } Catch(err) {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_OUT_PIN, err, "Expected ERR_NOT_OUT_PIN exception");
        printf("Success: Exception generated. Error code: %d.\n", err);
    }

    destroyModule(AND);
    destroyModule(OR);
}

void xtest_configureInputOutput_given_AND_and_OR_should_connect_output_from_OR_to_AND_through_a_pipe_module(void)
{
    Module *AND, *OR;

    int inputType = QUAD_2_INPUT, orOutPin = 9, andInPin = 1;

    OR = createdOrModule(inputType);
    AND = createdAndModule(inputType);

    // printf("(OR->pin[orOutPin-1]).type: %d\n", (OR->pin[orOutPin-1]).type);
    OR->configure((void *)OR, (void *)orOutPin, (void *)AND, (void *)andInPin);
    // printf("(OR->pin[orOutPin-1]).type: %d\n", (OR->pin[orOutPin-1]).type);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_NOT_NULL((OR->pin[orOutPin-1]).pipe);
    // TEST_ASSERT_EQUAL(AND, (OR->pin[orOutPin-1]).pipe)->moduleAndPin->module);

    destroyModule(AND);
    destroyModule(OR);
}