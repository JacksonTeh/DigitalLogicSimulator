#include <malloc.h>
#include <stdio.h>
#include "unity.h"
#include "DigitalSignalModule.h"
#include "InitNode.h"
#include "CException.h"
#include "mock_DigitalEventSimulator.h"
#include "mock_RedBlackTree.h"
#include "Rotations.h"

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
    }
}

void test_createdAndModule_given_QUAD_2_INPUT_type_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int i, inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL_STRING("AND", AND->name);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL(inputType, AND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, AND->totalPin);
    // TEST_ASSERT_EQUAL_PTR(NULL, AND->pipe);

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

    destroyModule(AND);
}

void test_createdAndModule_given_TRI_3_INPUT_type_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int i, inputType = TRI_3_INPUT;

    AND = createdAndModule(inputType);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL_STRING("AND", AND->name);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL(inputType, AND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, AND->totalPin);
    // TEST_ASSERT_EQUAL_PTR(NULL, AND->pipe);

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
    TEST_ASSERT_EQUAL_STRING("AND", AND->name);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
    TEST_ASSERT_EQUAL(inputType, AND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, AND->totalPin);
    // TEST_ASSERT_EQUAL_PTR(NULL, AND->pipe);

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

void test_storedModuleAndPin_should_store_module_and_pin(void)
{
    ModuleAndPin moduleAndPin;
    Module *AND;
    int inputType = DUAL_4_INPUT, andInPin = 1;

    AND = createdAndModule(inputType);
    storedModuleAndPin(&moduleAndPin, AND, andInPin);
    // moduleAndPin = storedModuleAndPin(AND, andInPin);

    TEST_ASSERT_EQUAL_PTR(AND, moduleAndPin.module);
    TEST_ASSERT_EQUAL_PTR(&AND->pin[andInPin], moduleAndPin.pin);

    destroyModule(AND);
    // destroyModuleAndPin(moduleAndPin);
}

void test_createdPipeModule_should_create_module_for_pipe(void)
{
    Pipe *pipe;
    Module *module;

    pipe = createdPipeModule();

    TEST_ASSERT_NOT_NULL(pipe);
    TEST_ASSERT_EQUAL_PTR(&pipeEvent, pipe->event);
    TEST_ASSERT_EQUAL_PTR(&setPipe, pipe->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, pipe->configure);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data);
    // TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->module);
    // TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->pin);
    // TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->left);
    // TEST_ASSERT_EQUAL_PTR(NULL, pipe->moduleAndPin->right);
    TEST_ASSERT_EQUAL(UNKNOWN, pipe->stateToFire);

    destroyPipe(pipe);
}
/*
void test_addPipeModuleData_should_add_AND_module_and_pin_to_the_pipe_module_data(void)
{
    Pipe *pipe;
    Module *AND;
    ModuleAndPin *moduleAND;
    Node newNode;
    int inputType = QUAD_2_INPUT, pinNum = 1;

    // printf("\ntest_addPipeModuleData_should_add_AND_module_and_pin_to_the_pipe_module_data\n");
    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    // pipe->moduleAndPin->module = AND;
    // pipe->moduleAndPin->pin = &AND->pin[0];
    moduleAND = createdModuleAndPin(AND, pinNum);

    genericResetNode(&newNode, (void *)moduleAND);

    addPipeModuleData(&pipe, &newNode);

    TEST_ASSERT_NOT_NULL(pipe);
    TEST_ASSERT_EQUAL_PTR(&pipeEvent, pipe->event);
    TEST_ASSERT_EQUAL_PTR(&setPipe, pipe->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, pipe->configure);
    TEST_ASSERT_EQUAL_PTR(&newNode, pipe->data);
    TEST_ASSERT_EQUAL_PTR((void *)moduleAND, pipe->data->dataPtr);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data->left);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data->right);
    TEST_ASSERT_EQUAL_PTR(UNKNOWN, pipe->stateToFire);

    // destroyModuleAndPin(moduleAND);
    destroyModule(AND);
    destroyPipe(pipe);
}

void test_addPipeModuleData_given_AND_module_and_pin_in_pipe_module_data_should_add_OR_module_and_pin_to_the_pipe_module_data(void)
{
    Pipe *pipe;
    Module *AND, *OR;
    ModuleAndPin *moduleAND, *moduleOR;
    Node root, newNode;
    int inputType = QUAD_2_INPUT, pinNum = 1;

    // printf("\ntest_addPipeModuleData_given_AND_module_and_pin_in_pipe_module_data_should_add_OR_module_and_pin_to_the_pipe_module_data\n");
    AND = createdAndModule(inputType);
    OR = createdOrModule(inputType);
    pipe = createdPipeModule();
    // pipe->moduleAndPin->module = AND;
    // pipe->moduleAndPin->pin = &AND->pin[0];
    moduleAND = createdModuleAndPin(AND, pinNum);
    moduleOR = createdModuleAndPin(OR, pinNum);

    genericResetNode(&root, (void *)moduleAND);
    genericResetNode(&newNode, (void *)moduleOR);
    setNode(&newNode, NULL, NULL, 'r');
    setNode(&root, NULL, NULL, 'b');
    pipe->data = &root;

    addPipeModuleData(&pipe, &newNode);

    TEST_ASSERT_NOT_NULL(pipe);
    TEST_ASSERT_EQUAL_PTR(&pipeEvent, pipe->event);
    TEST_ASSERT_EQUAL_PTR(&setPipe, pipe->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, pipe->configure);
    TEST_ASSERT_EQUAL_PTR((void *)moduleAND, pipe->data->dataPtr);
    TEST_ASSERT_EQUAL_PTR((void *)moduleOR, pipe->data->right->dataPtr);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data->right->left);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data->right->right);
    TEST_ASSERT_EQUAL_PTR(NULL, pipe->data->left);
    TEST_ASSERT_EQUAL_PTR(UNKNOWN, pipe->stateToFire);

    // destroyModuleAndPin(moduleAND);
    // destroyModuleAndPin(moduleOR);
    destroyModule(AND);
    destroyModule(OR);
    destroyPipe(pipe);
} */
/*
void test_pipeAttach_given_module_AND_in_pipe_module_data_should_attach_pipe_module_to_AND_module(void)
{
    Pipe *pipe;
    Module *AND;
    ModuleAndPin *moduleAND, *moduleAndPin;
    Node root;
    int inputType = QUAD_2_INPUT, pinNum = 1;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    moduleAND = createdModuleAndPin(AND, pinNum);

    genericResetNode(&root, (void *)moduleAND);
    setNode(&root, NULL, NULL, 'b');
    pipe->data = &root;
    moduleAndPin = (ModuleAndPin *)pipe->data->dataPtr;
    // printf("pipe: %p\n", pipe);
    // printf("pipe->moduleAndPin: %p\n", pipe->moduleAndPin);
    // printf("pipe->moduleAndPin->module: %p\n", pipe->moduleAndPin->module);
    // printf("pipe->moduleAndPin->pin: %p\n", pipe->moduleAndPin->pin);
    // printf("AND: %p\n", AND);
    // printf("AND->pin[andInPin-1]: %p\n", &AND->pin[andInPin-1]);
    // printf("AND->pin[andInPin]: %p\n", &AND->pin[andInPin]);
    pipeAttach(&pipe, AND, &pinNum);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(pipe);
    // TEST_ASSERT_EQUAL_PTR(AND, (Module *)pipe->data->dataPtr->module);
    TEST_ASSERT_EQUAL_PTR(AND, moduleAndPin->module);
    // TEST_ASSERT_EQUAL_PTR(&AND->pin[pinNum-1], (Pin *)pipe->data->dataPtr->pin);

    destroyModuleAndPin(moduleAND);
    destroyModule(AND);
    destroyPipe(pipe);
} */

void test_configureInputOutput_given_invalid_output_pin_for_OR_module_should_throw_ERR_NOT_OUT_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND, *OR;
    // Node newNode = NULL;

    int inputType = QUAD_2_INPUT;

    // printf("\ntest_configureInputOutput_given_invalid_output_pin_for_OR_module_should_throw_ERR_NOT_OUT_PIN\n");
    Try{
        OR = createdOrModule(inputType);
        AND = createdAndModule(inputType);
        OR->configure((void *)OR, (void *)&OR->pin[1], (void *)AND, (void *)&AND->pin[0], NULL);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_NOT_OUT_PIN.");
    } Catch(err) {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_OUT_PIN, err, "Expected ERR_NOT_OUT_PIN exception");
    }

    destroyModule(AND);
    destroyModule(OR);
}

void test_configureInputOutput_given_invalid_input_pin_for_AND_module_should_throw_ERR_NOT_IN_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND, *OR;
    // Node newNode = NULL;

    int inputType = QUAD_2_INPUT;

    // printf("\ntest_configureInputOutput_given_invalid_input_pin_for_AND_module_should_throw_ERR_NOT_IN_PIN\n");
    Try{
        OR = createdOrModule(inputType);
        AND = createdAndModule(inputType);
        OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[9], NULL);
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
    // Node newNode = NULL;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    AND = createdAndModule(inputType);

    // printf("\ntest_configureInputOutput_given_AND_and_OR_should_connect_output_from_OR_to_a_pipe_module\n");
    OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[0], NULL);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_NOT_NULL((OR->pin[9]).pipe);
    // TEST_ASSERT_NOT_NULL(OR->pipe);
    // TEST_ASSERT_EQUAL(&OR->pin[9], OR->pipe->inPin);

    destroyModule(AND);
    destroyModule(OR);
}

void test_configureInputOutput_given_AND_and_OR_that_connected_to_pipe_should_connect_output_from_pipe_to_AND_module_and_add_data_to_pipe(void)
{
    Module *AND, *OR;
    Pipe *pipe;
    // ModuleAndPin pipeData = {AND, &AND->pin[0]};
    ModuleAndPin pipeData;
    Node newNode;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    // storedModuleAndPin(&pipeData, AND, (AND->pin[0]).pinNumber);
    // pipeData = storedModuleAndPin(AND, (AND->pin[0]).pinNumber);

    genericResetNode(&newNode, (void *)&pipeData);
    // setNode(&newNode, NULL, NULL, 'r');

    (OR->pin[9]).pipe = pipe;

    genericAddRedBlackTree_Expect(&((OR->pin[9]).pipe)->data, &newNode, compareModuleAndPin);

    // printf("\ntest_configureInputOutput_given_AND_and_OR_should_connect_output_from_OR_to_a_pipe_module\n");
    OR->configure((void *)OR, (void *)&OR->pin[9], (void *)AND, (void *)&AND->pin[0], &newNode);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_NOT_NULL((OR->pin[9]).pipe);
    // TEST_ASSERT_EQUAL(((OR->pin[9]).pipe)->stateToFire, (AND->pin[0]).state);
    TEST_ASSERT_EQUAL_PTR((OR->pin[9]).pipe, (AND->pin[0]).pipe);

    // destroyModuleAndPin(pipeData);
    destroyModule(AND);
    destroyModule(OR);
}

void xtest_setAnd_given_AND_should_set_input_of_AND_module_and_register_event(void)
{
    Module *AND;
    ModuleAndPin moduleAndPin;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    storedModuleAndPin(&moduleAndPin, AND, (AND->pin[0]).pinNumber);
    // moduleAndPin = createdModuleAndPin(AND, (&AND->pin[0])->pinNumber);
    // moduleAndPin.module = AND;
    // moduleAndPin.pin = &AND->pin[0];

    // printf("moduleAndPin: %p\n", &moduleAndPin);
    registerEvent_Expect(&moduleAndPin, NULL, ONE_NANO_SEC);

    // AND->set((void *)AND, (void *)&AND->pin[0], HIGH, ONE_NANO_SEC);
    AND->set((void *)&moduleAndPin, HIGH, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, (AND->pin[0]).state);

    // destroyModuleAndPin(moduleAndPin);
    destroyModule(AND);
}

void xtest_andEvent_given_AND_should_set_the_pipe(void)
{
    Module *AND;
    ModuleAndPin moduleAndPin;
    Pipe *pipe;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    (AND->pin[8]).pipe = pipe;
    (AND->pin[0]).state = HIGH;
    moduleAndPin.module = AND;
    moduleAndPin.pin = &AND->pin[0];

    AND->configure((void *)AND, (void *)&AND->pin[8], NULL, NULL, NULL);

    // registerEvent_Expect(NULL, ONE_NANO_SEC);

    // AND->event((void *)moduleAndPin);

    destroyModule(AND);
}

void xtest_setPipe_given_pipe_with_AND_module_data_should_register_event_for_pipe(void)
{
    Module *AND;
    ModuleAndPin *pipeData;
    Pipe *pipe;
    Node newNode;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    // pipeData = createdModuleAndPin(AND, (&AND->pin[0])->pinNumber);
    // pipeData.module = AND;
    // pipeData.pin = &AND->pin[0];

    genericResetNode(&newNode, (void *)&pipeData);
    setNode(&newNode, NULL, NULL, 'r');
    pipe->data = &newNode;

    // registerEvent_Expect(&pipeData, pipe, ONE_NANO_SEC);

    // AND->set((void *)AND, (void *)&AND->pin[0], HIGH, ONE_NANO_SEC);
    pipe->set((void *)pipe, (void *)pipe->data, HIGH, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, pipe->stateToFire);

    destroyModule(AND);
    destroyPipe(pipe);
}