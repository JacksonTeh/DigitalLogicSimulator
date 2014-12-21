#include <malloc.h>
#include <stdio.h>
#include "unity.h"
#include "DigitalSignalModule.h"
#include "InitNode.h"
#include "CException.h"
#include "mock_DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "Rotations.h"
#include "Node.h"
#include "EventInfo.h"

extern Node *eventRoot;

void setUp(void)
{
    eventRoot = NULL;
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

void test_createdXorModule_given_DUAL_4_INPUT_type_should_thrown_ERR_INVALID_INPUT_TYPE(void)
{
    CEXCEPTION_T err;
    Module *XOR;
    int inputType = DUAL_4_INPUT;

    Try{
        XOR = createdXorModule(inputType);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_INVALID_INPUT_TYPE.");
    } Catch(err){
        TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_INPUT_TYPE, err, "Expected ERR_INVALID_INPUT_TYPE exception");
    }
}

void test_createdNotModule_given_other_than_HEX_INV_type_should_thrown_ERR_INVALID_INPUT_TYPE(void)
{
    CEXCEPTION_T err;
    Module *NOT;
    int inputType = QUAD_2_INPUT;

    Try{
        NOT = createdNotModule(inputType);
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

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (AND->pin[i]).state);
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

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (AND->pin[i]).state);
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

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (AND->pin[i]).type);
        else if(i > 7 && i < 10)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (AND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (AND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (AND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (AND->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (AND->pin[i]).pipe);
    }

    destroyModule(AND);
}

void test_createdOrModule_given_QUAD_2_INPUT_type_should_create_module_for_OR_gate(void)
{
    Module *OR;
    int i, inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);

    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_EQUAL_STRING("OR", OR->name);
    TEST_ASSERT_EQUAL_PTR(&orEvent, OR->event);
    TEST_ASSERT_EQUAL_PTR(&setOr, OR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, OR->configure);
    TEST_ASSERT_EQUAL(inputType, OR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, OR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (OR->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (OR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (OR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (OR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (OR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (OR->pin[i]).pipe);
    }

    destroyModule(OR);
}

void test_createdOrModule_given_TRI_3_INPUT_type_should_create_module_for_OR_gate(void)
{
    Module *OR;
    int i, inputType = TRI_3_INPUT;

    OR = createdOrModule(inputType);

    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_EQUAL_STRING("OR", OR->name);
    TEST_ASSERT_EQUAL_PTR(&orEvent, OR->event);
    TEST_ASSERT_EQUAL_PTR(&setOr, OR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, OR->configure);
    TEST_ASSERT_EQUAL(inputType, OR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, OR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (OR->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (OR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (OR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (OR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (OR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (OR->pin[i]).pipe);
    }

    destroyModule(OR);
}

void test_createdOrModule_given_DUAL_4_INPUT_type_should_create_module_for_OR_gate(void)
{
    Module *OR;
    int i, inputType = DUAL_4_INPUT;

    OR = createdOrModule(inputType);

    TEST_ASSERT_NOT_NULL(OR);
    TEST_ASSERT_EQUAL_STRING("OR", OR->name);
    TEST_ASSERT_EQUAL_PTR(&orEvent, OR->event);
    TEST_ASSERT_EQUAL_PTR(&setOr, OR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, OR->configure);
    TEST_ASSERT_EQUAL(inputType, OR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, OR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (OR->pin[i]).type);
        else if(i > 7 && i < 10)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (OR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (OR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (OR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (OR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (OR->pin[i]).pipe);
    }

    destroyModule(OR);
}

void test_createdXorModule_given_QUAD_2_INPUT_type_should_create_module_for_XOR_gate(void)
{
    Module *XOR;
    int i, inputType = QUAD_2_INPUT;

    XOR = createdXorModule(inputType);

    TEST_ASSERT_NOT_NULL(XOR);
    TEST_ASSERT_EQUAL_STRING("XOR", XOR->name);
    TEST_ASSERT_EQUAL_PTR(&xorEvent, XOR->event);
    TEST_ASSERT_EQUAL_PTR(&setXor, XOR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, XOR->configure);
    TEST_ASSERT_EQUAL(inputType, XOR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, XOR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (XOR->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (XOR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (XOR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (XOR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (XOR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (XOR->pin[i]).pipe);
    }

    destroyModule(XOR);
}

void test_createdXorModule_given_TRI_3_INPUT_type_should_create_module_for_XOR_gate(void)
{
    Module *XOR;
    int i, inputType = TRI_3_INPUT;

    XOR = createdXorModule(inputType);

    TEST_ASSERT_NOT_NULL(XOR);
    TEST_ASSERT_EQUAL_STRING("XOR", XOR->name);
    TEST_ASSERT_EQUAL_PTR(&xorEvent, XOR->event);
    TEST_ASSERT_EQUAL_PTR(&setXor, XOR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, XOR->configure);
    TEST_ASSERT_EQUAL(inputType, XOR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, XOR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (XOR->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (XOR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (XOR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (XOR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (XOR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (XOR->pin[i]).pipe);
    }

    destroyModule(XOR);
}

void test_createdNandModule_given_QUAD_2_INPUT_type_should_create_module_for_NAND_gate(void)
{
    Module *NAND;
    int i, inputType = QUAD_2_INPUT;

    NAND = createdNandModule(inputType);

    TEST_ASSERT_NOT_NULL(NAND);
    TEST_ASSERT_EQUAL_STRING("NAND", NAND->name);
    TEST_ASSERT_EQUAL_PTR(&nandEvent, NAND->event);
    TEST_ASSERT_EQUAL_PTR(&setNand, NAND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NAND->configure);
    TEST_ASSERT_EQUAL(inputType, NAND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NAND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NAND->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NAND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NAND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NAND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NAND->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NAND->pin[i]).pipe);
    }

    destroyModule(NAND);
}

void test_createdNandModule_given_TRI_3_INPUT_type_should_create_module_for_NAND_gate(void)
{
    Module *NAND;
    int i, inputType = TRI_3_INPUT;

    NAND = createdNandModule(inputType);

    TEST_ASSERT_NOT_NULL(NAND);
    TEST_ASSERT_EQUAL_STRING("NAND", NAND->name);
    TEST_ASSERT_EQUAL_PTR(&nandEvent, NAND->event);
    TEST_ASSERT_EQUAL_PTR(&setNand, NAND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NAND->configure);
    TEST_ASSERT_EQUAL(inputType, NAND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NAND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NAND->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NAND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NAND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NAND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NAND->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NAND->pin[i]).pipe);
    }

    destroyModule(NAND);
}

void test_createdNandModule_given_DUAL_4_INPUT_type_should_create_module_for_NAND_gate(void)
{
    Module *NAND;
    int i, inputType = DUAL_4_INPUT;

    NAND = createdNandModule(inputType);

    TEST_ASSERT_NOT_NULL(NAND);
    TEST_ASSERT_EQUAL_STRING("NAND", NAND->name);
    TEST_ASSERT_EQUAL_PTR(&nandEvent, NAND->event);
    TEST_ASSERT_EQUAL_PTR(&setNand, NAND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NAND->configure);
    TEST_ASSERT_EQUAL(inputType, NAND->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NAND->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NAND->pin[i]).type);
        else if(i > 7 && i < 10)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NAND->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NAND->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NAND->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NAND->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NAND->pin[i]).pipe);
    }

    destroyModule(NAND);
}

void test_createdNorModule_given_QUAD_2_INPUT_type_should_create_module_for_NOR_gate(void)
{
    Module *NOR;
    int i, inputType = QUAD_2_INPUT;

    NOR = createdNorModule(inputType);

    TEST_ASSERT_NOT_NULL(NOR);
    TEST_ASSERT_EQUAL_STRING("NOR", NOR->name);
    TEST_ASSERT_EQUAL_PTR(&norEvent, NOR->event);
    TEST_ASSERT_EQUAL_PTR(&setNor, NOR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NOR->configure);
    TEST_ASSERT_EQUAL(inputType, NOR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NOR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NOR->pin[i]).type);
        else if(i > 7 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NOR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NOR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NOR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NOR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NOR->pin[i]).pipe);
    }

    destroyModule(NOR);
}

void test_createdNorModule_given_TRI_3_INPUT_type_should_create_module_for_NOR_gate(void)
{
    Module *NOR;
    int i, inputType = TRI_3_INPUT;

    NOR = createdNorModule(inputType);

    TEST_ASSERT_NOT_NULL(NOR);
    TEST_ASSERT_EQUAL_STRING("NOR", NOR->name);
    TEST_ASSERT_EQUAL_PTR(&norEvent, NOR->event);
    TEST_ASSERT_EQUAL_PTR(&setNor, NOR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NOR->configure);
    TEST_ASSERT_EQUAL(inputType, NOR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NOR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 9)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NOR->pin[i]).type);
        else if(i > 8 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NOR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NOR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NOR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NOR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NOR->pin[i]).pipe);
    }

    destroyModule(NOR);
}

void test_createdNorModule_given_DUAL_4_INPUT_type_should_create_module_for_MOR_gate(void)
{
    Module *NOR;
    int i, inputType = DUAL_4_INPUT;

    NOR = createdNorModule(inputType);

    TEST_ASSERT_NOT_NULL(NOR);
    TEST_ASSERT_EQUAL_STRING("NOR", NOR->name);
    TEST_ASSERT_EQUAL_PTR(&norEvent, NOR->event);
    TEST_ASSERT_EQUAL_PTR(&setNor, NOR->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NOR->configure);
    TEST_ASSERT_EQUAL(inputType, NOR->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NOR->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 8)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NOR->pin[i]).type);
        else if(i > 7 && i < 10)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NOR->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NOR->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NOR->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NOR->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NOR->pin[i]).pipe);
    }

    destroyModule(NOR);
}

void test_createdNotModule_given_HEX_INV_type_should_create_module_for_NOT_gate(void)
{
    Module *NOT;
    int i, inputType = HEX_INV;

    NOT = createdNotModule(inputType);

    TEST_ASSERT_NOT_NULL(NOT);
    TEST_ASSERT_EQUAL_STRING("NOT", NOT->name);
    TEST_ASSERT_EQUAL_PTR(&notEvent, NOT->event);
    TEST_ASSERT_EQUAL_PTR(&setNot, NOT->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NOT->configure);
    TEST_ASSERT_EQUAL(inputType, NOT->typeOfInput);
    TEST_ASSERT_EQUAL(TOTAL_PIN, NOT->totalPin);

    for(i = 0; i < TOTAL_PIN; i++)
    {
        if(i < 6)
            TEST_ASSERT_EQUAL(INPUT_PIN, (NOT->pin[i]).type);
        else if(i > 5 && i < 12)
            TEST_ASSERT_EQUAL(OUTPUT_PIN, (NOT->pin[i]).type);
        else
            TEST_ASSERT_EQUAL(UNUSED_PIN, (NOT->pin[i]).type);

        TEST_ASSERT_EQUAL(i, (NOT->pin[i]).pinNumber);
        TEST_ASSERT_EQUAL(LOW, (NOT->pin[i]).state);
        TEST_ASSERT_EQUAL_PTR(NULL, (NOT->pin[i]).pipe);
    }

    destroyModule(NOT);
}

// void test_storedModuleAndPin_should_store_module_and_pin(void)
// {
    // ModuleAndPin moduleAndPin;
    // Module *AND;
    // int inputType = DUAL_4_INPUT, andInPin = 1;

    // AND = createdAndModule(inputType);
    // storedModuleAndPin(&moduleAndPin, AND, andInPin);

    // TEST_ASSERT_EQUAL_PTR(AND, moduleAndPin.module);
    // TEST_ASSERT_EQUAL_PTR(&AND->pin[andInPin], moduleAndPin.pin);

    // destroyModule(AND);
// }

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
    TEST_ASSERT_EQUAL(UNKNOWN, pipe->stateToFire);

    destroyPipeData(pipe);
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

void test_configureInputOutput_given_invalid_output_pin_for_OR_module_should_throw_ERR_NOT_OUT_PIN(void)
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

void test_configureInputOutput_given_invalid_input_pin_for_AND_module_should_throw_ERR_NOT_IN_PIN(void)
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

void test_setAnd_given_AND_module_should_set_input_of_AND_module_and_register_event(void)
{
    Module *AND;
    ModuleAndPin *moduleAndPin;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[0]).pinNumber);

    registerEvent_Expect(moduleAndPin, NULL, ONE_NANO_SEC + AND_PROPAGATION_DELAY);

    AND->set((void *)moduleAndPin, HIGH, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, (AND->pin[0]).state);

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_setAnd_given_AND_module_and_set_output_of_AND_module_should_throw_ERR_NOT_IN_PIN(void)
{
    CEXCEPTION_T err;
    Module *AND;
    ModuleAndPin *moduleAndPin;
    Node timeNode;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[9]).pinNumber);

    Try{
        AND->set((void *)moduleAndPin, HIGH, ONE_NANO_SEC);
        TEST_FAIL_MESSAGE("Should generate an exception due to ERR_NOT_IN_PIN.");
    } Catch(err) {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NOT_IN_PIN, err, "Expected ERR_NOT_IN_PIN exception");
    }

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_andEvent_given_AND_with_QUAD_2_INPUT_should_generate_event_for_AND_module(void)
{
    Module *AND, *module;
    ModuleAndPin *moduleAndPin;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[6]).state = HIGH;
    (AND->pin[7]).state = HIGH;
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[6]).pinNumber);

    AND->event((void *)moduleAndPin, ONE_NANO_SEC);
    module = moduleAndPin->module;

    TEST_ASSERT_EQUAL(HIGH, (module->pin[11]).state);

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_andEvent_given_AND_with_TRI_3_INPUT_should_generate_event_for_AND_module(void)
{
    Module *AND, *module;
    ModuleAndPin *moduleAndPin;
    int inputType = TRI_3_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[3]).state = HIGH;
    (AND->pin[4]).state = HIGH;
    (AND->pin[5]).state = HIGH;
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[4]).pinNumber);

    AND->event((void *)moduleAndPin, ONE_NANO_SEC);
    module = moduleAndPin->module;

    TEST_ASSERT_EQUAL(HIGH, (module->pin[10]).state);

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_andEvent_given_AND_with_DUAL_4_INPUT_should_generate_event_for_AND_module(void)
{
    Module *AND, *module;
    ModuleAndPin *moduleAndPin;
    int inputType = DUAL_4_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[4]).state = HIGH;
    (AND->pin[5]).state = HIGH;
    (AND->pin[6]).state = HIGH;
    (AND->pin[7]).state = HIGH;
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[5]).pinNumber);

    AND->event((void *)moduleAndPin, ONE_NANO_SEC);
    module = moduleAndPin->module;

    TEST_ASSERT_EQUAL(HIGH, (module->pin[9]).state);

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_andEvent_given_AND_with_QUAD_2_INPUT_and_connected_to_pipe_should_register_event_for_pipe(void)
{
    Module *AND, *module;
    ModuleAndPin *moduleAndPin;
    Pipe *pipe;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[6]).state = HIGH;
    (AND->pin[7]).state = HIGH;
    pipe = createdPipeModule();
    AND->pin[11].pipe = pipe;
    moduleAndPin = createdModuleAndPin(AND, (AND->pin[6]).pinNumber);

    registerEvent_Expect(NULL, pipe, ONE_NANO_SEC);

    AND->event((void *)moduleAndPin, ONE_NANO_SEC);
    module = moduleAndPin->module;

    TEST_ASSERT_EQUAL(HIGH, (module->pin[11]).state);

    destroyModule(AND);
    destroyModuleAndPin(moduleAndPin);
}

void test_notEvent_given_NOT_should_generate_event_for_NOT_module(void)
{
    Module *NOT, *module;
    ModuleAndPin *moduleAndPin;
    int inputType = HEX_INV;

    NOT = createdNotModule(inputType);
    (NOT->pin[4]).state = HIGH;

    moduleAndPin = createdModuleAndPin(NOT, (NOT->pin[4]).pinNumber);

    NOT->event((void *)moduleAndPin, ONE_NANO_SEC);
    module = moduleAndPin->module;

    TEST_ASSERT_EQUAL(LOW, (module->pin[10]).state);

    destroyModule(NOT);
    destroyModuleAndPin(moduleAndPin);
}

void test_funcOfAND_given_QUAD_2_INPUT_AND_and_HIGH_in_both_input_should_return_HIGH(void)
{
    Module *AND;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfAND(AND, AND->pin[0].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfAND_given_QUAD_2_INPUT_AND_and_either_one_input_LOW_should_return_LOW(void)
{
    Module *AND;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfAND(AND, AND->pin[0].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfAND_given_TRI_3_INPUT_AND_and_HIGH_in_all_input_should_return_HIGH(void)
{
    Module *AND;
    int inputType = TRI_3_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[6]).state = HIGH;
    (AND->pin[7]).state = HIGH;
    (AND->pin[8]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfAND(AND, AND->pin[6].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfAND_given_TRI_3_INPUT_AND_and_either_one_input_LOW_should_return_LOW(void)
{
    Module *AND;
    int inputType = TRI_3_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = LOW;
    (AND->pin[2]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfAND(AND, AND->pin[0].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfAND_given_DUAL_4_INPUT_AND_and_HIGH_in_all_input_should_return_HIGH(void)
{
    Module *AND;
    int inputType = DUAL_4_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = HIGH;
    (AND->pin[2]).state = HIGH;
    (AND->pin[3]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfAND(AND, AND->pin[0].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfAND_given_DUAL_4_INPUT_AND_and_either_one_input_LOW_should_return_LOW(void)
{
    Module *AND;
    int inputType = DUAL_4_INPUT;

    AND = createdAndModule(inputType);
    (AND->pin[0]).state = HIGH;
    (AND->pin[1]).state = LOW;
    (AND->pin[2]).state = HIGH;
    (AND->pin[3]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfAND(AND, AND->pin[0].pinNumber, inputType));

    destroyModule(AND);
}

void test_funcOfOR_given_QUAD_2_INPUT_OR_and_LOW_in_both_input_should_return_LOW(void)
{
    Module *OR;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[0]).state = LOW;
    (OR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfOR(OR, OR->pin[0].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfOR_given_QUAD_2_INPUT_OR_and_either_one_input_HIGH_should_return_HIGH(void)
{
    Module *OR;
    int inputType = QUAD_2_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[0]).state = HIGH;
    (OR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfOR(OR, OR->pin[0].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfOR_given_TRI_3_INPUT_OR_and_LOW_in_all_input_should_return_LOW(void)
{
    Module *OR;
    int inputType = TRI_3_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[6]).state = LOW;
    (OR->pin[7]).state = LOW;
    (OR->pin[8]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfOR(OR, OR->pin[6].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfOR_given_TRI_3_INPUT_OR_and_either_one_input_HIGH_should_return_HIGH(void)
{
    Module *OR;
    int inputType = TRI_3_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[0]).state = LOW;
    (OR->pin[1]).state = LOW;
    (OR->pin[2]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfOR(OR, OR->pin[0].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfOR_given_DUAL_4_INPUT_OR_and_LOW_in_all_input_should_return_LOW(void)
{
    Module *OR;
    int inputType = DUAL_4_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[0]).state = LOW;
    (OR->pin[1]).state = LOW;
    (OR->pin[2]).state = LOW;
    (OR->pin[3]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfOR(OR, OR->pin[0].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfOR_given_DUAL_4_INPUT_OR_and_either_one_input_HIGH_should_return_HIGH(void)
{
    Module *OR;
    int inputType = DUAL_4_INPUT;

    OR = createdOrModule(inputType);
    (OR->pin[0]).state = LOW;
    (OR->pin[1]).state = LOW;
    (OR->pin[2]).state = HIGH;
    (OR->pin[3]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfOR(OR, OR->pin[0].pinNumber, inputType));

    destroyModule(OR);
}

void test_funcOfXOR_given_QUAD_2_INPUT_XOR_and_both_input_are_different_state_should_return_HIGH(void)
{
    Module *XOR;
    int inputType = QUAD_2_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[0]).state = HIGH;
    (XOR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfXOR(XOR, XOR->pin[0].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfXOR_given_QUAD_2_INPUT_XOR_and_both_input_are_same_state_should_return_LOW(void)
{
    Module *XOR;
    int inputType = QUAD_2_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[0]).state = LOW;
    (XOR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfXOR(XOR, XOR->pin[0].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfXOR_given_TRI_3_INPUT_XOR_and_either_one_input_HIGH_should_return_HIGH(void)
{
    Module *XOR;
    int inputType = TRI_3_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[6]).state = LOW;
    (XOR->pin[7]).state = HIGH;
    (XOR->pin[8]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfXOR(XOR, XOR->pin[6].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfXOR_given_TRI_3_INPUT_XOR_and_all_input_HIGH_should_return_HIGH(void)
{
    Module *XOR;
    int inputType = TRI_3_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[6]).state = HIGH;
    (XOR->pin[7]).state = HIGH;
    (XOR->pin[8]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfXOR(XOR, XOR->pin[6].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfXOR_given_TRI_3_INPUT_XOR_and_either_two_input_HIGH_should_return_LOW(void)
{
    Module *XOR;
    int inputType = TRI_3_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[0]).state = HIGH;
    (XOR->pin[1]).state = LOW;
    (XOR->pin[2]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfXOR(XOR, XOR->pin[0].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfXOR_given_TRI_3_INPUT_XOR_and_all_input_LOW_should_return_LOW(void)
{
    Module *XOR;
    int inputType = TRI_3_INPUT;

    XOR = createdXorModule(inputType);
    (XOR->pin[0]).state = LOW;
    (XOR->pin[1]).state = LOW;
    (XOR->pin[2]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfXOR(XOR, XOR->pin[0].pinNumber, inputType));

    destroyModule(XOR);
}

void test_funcOfNAND_given_QUAD_2_INPUT_NAND_and_HIGH_in_both_input_should_return_LOW(void)
{
    Module *NAND;
    int inputType = QUAD_2_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[0]).state = HIGH;
    (NAND->pin[1]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfNAND(NAND, NAND->pin[0].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNAND_given_QUAD_2_INPUT_NAND_and_either_one_input_LOW_should_return_HIGH(void)
{
    Module *NAND;
    int inputType = QUAD_2_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[0]).state = HIGH;
    (NAND->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfNAND(NAND, NAND->pin[0].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNAND_given_TRI_3_INPUT_NAND_and_HIGH_in_all_input_should_return_LOW(void)
{
    Module *NAND;
    int inputType = TRI_3_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[6]).state = HIGH;
    (NAND->pin[7]).state = HIGH;
    (NAND->pin[8]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfNAND(NAND, NAND->pin[6].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNAND_given_TRI_3_INPUT_NAND_and_either_one_input_LOW_should_return_HIGH(void)
{
    Module *NAND;
    int inputType = TRI_3_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[0]).state = HIGH;
    (NAND->pin[1]).state = LOW;
    (NAND->pin[2]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfNAND(NAND, NAND->pin[0].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNAND_given_DUAL_4_INPUT_NAND_and_HIGH_in_all_input_should_return_LOW(void)
{
    Module *NAND;
    int inputType = DUAL_4_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[0]).state = HIGH;
    (NAND->pin[1]).state = HIGH;
    (NAND->pin[2]).state = HIGH;
    (NAND->pin[3]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfNAND(NAND, NAND->pin[0].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNAND_given_DUAL_4_INPUT_NAND_and_either_one_input_LOW_should_return_HIGH(void)
{
    Module *NAND;
    int inputType = DUAL_4_INPUT;

    NAND = createdNandModule(inputType);
    (NAND->pin[0]).state = HIGH;
    (NAND->pin[1]).state = LOW;
    (NAND->pin[2]).state = HIGH;
    (NAND->pin[3]).state = HIGH;

    TEST_ASSERT_EQUAL(HIGH, funcOfNAND(NAND, NAND->pin[0].pinNumber, inputType));

    destroyModule(NAND);
}

void test_funcOfNOR_given_QUAD_2_INPUT_NOR_and_LOW_in_both_input_should_return_HIGH(void)
{
    Module *NOR;
    int inputType = QUAD_2_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[0]).state = LOW;
    (NOR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfNOR(NOR, NOR->pin[0].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOR_given_QUAD_2_INPUT_NOR_and_either_one_input_HIGH_should_return_LOW(void)
{
    Module *NOR;
    int inputType = QUAD_2_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[0]).state = HIGH;
    (NOR->pin[1]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfNOR(NOR, NOR->pin[0].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOR_given_TRI_3_INPUT_NOR_and_LOW_in_all_input_should_return_HIGH(void)
{
    Module *NOR;
    int inputType = TRI_3_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[6]).state = LOW;
    (NOR->pin[7]).state = LOW;
    (NOR->pin[8]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfNOR(NOR, NOR->pin[6].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOR_given_TRI_3_INPUT_NOR_and_either_one_input_HIGH_should_return_LOW(void)
{
    Module *NOR;
    int inputType = TRI_3_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[0]).state = LOW;
    (NOR->pin[1]).state = LOW;
    (NOR->pin[2]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfNOR(NOR, NOR->pin[0].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOR_given_DUAL_4_INPUT_NOR_and_LOW_in_all_input_should_return_HIGH(void)
{
    Module *NOR;
    int inputType = DUAL_4_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[0]).state = LOW;
    (NOR->pin[1]).state = LOW;
    (NOR->pin[2]).state = LOW;
    (NOR->pin[3]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfNOR(NOR, NOR->pin[0].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOR_given_DUAL_4_INPUT_NOR_and_either_one_input_HIGH_should_return_LOW(void)
{
    Module *NOR;
    int inputType = DUAL_4_INPUT;

    NOR = createdNorModule(inputType);
    (NOR->pin[0]).state = LOW;
    (NOR->pin[1]).state = LOW;
    (NOR->pin[2]).state = HIGH;
    (NOR->pin[3]).state = LOW;

    TEST_ASSERT_EQUAL(LOW, funcOfNOR(NOR, NOR->pin[0].pinNumber, inputType));

    destroyModule(NOR);
}

void test_funcOfNOT_given_HEX_INV_NOT_and_LOW_in_input_should_return_HIGH(void)
{
    Module *NOT;
    int inputType = HEX_INV;

    NOT = createdNotModule(inputType);
    (NOT->pin[0]).state = LOW;

    TEST_ASSERT_EQUAL(HIGH, funcOfNOT(NOT, NOT->pin[0].pinNumber));

    destroyModule(NOT);
}

void test_funcOfNOT_given_HEX_INV_NOT_and_HIGH_in_input_should_return_LOW(void)
{
    Module *NOT;
    int inputType = HEX_INV;

    NOT = createdNotModule(inputType);
    (NOT->pin[3]).state = HIGH;

    TEST_ASSERT_EQUAL(LOW, funcOfNOT(NOT, NOT->pin[3].pinNumber));

    destroyModule(NOT);
}

void test_outputConnectionForHexInv_given_pin_5_should_return_11(void)
{
    Module *NOT;
    int inputType = HEX_INV;

    NOT = createdNotModule(inputType);

    TEST_ASSERT_EQUAL(11, outputConnectionForHexInv(NOT, 5, funcOfNOT));
}

void test_setPipe_given_pipe_should_register_event_for_pipe(void)
{
    Pipe *pipe;
    Node newNode;
    int inputType = QUAD_2_INPUT;

    pipe = createdPipeModule();
    pipe->stateToFire = LOW;

    registerEvent_Expect(NULL, pipe, ONE_NANO_SEC);

    pipe->set((void *)pipe, HIGH, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, pipe->stateToFire);

    destroyPipeData(pipe);
}
 
void test_pipeEvent_given_pipe_with_AND_module_data_should_register_event_for_pipe_data(void)
{
    Module *AND;
    ModuleAndPin *pipeData;
    Pipe *pipe;
    Node newNode;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    pipe = createdPipeModule();
    pipe->stateToFire = HIGH;
    // storedModuleAndPin(&pipeData, AND, (AND->pin[0]).pinNumber);
    pipeData = createdModuleAndPin(AND, (AND->pin[0]).pinNumber);

    genericSetNode(&newNode, (void *)pipeData, NULL, NULL, 'r');
    pipe->data = &newNode;

    registerEvent_Expect(pipeData, NULL, ONE_NANO_SEC + AND_PROPAGATION_DELAY);

    pipe->event((void *)pipe, (void *)pipe->data, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, (AND->pin[0]).state);

    destroyModule(AND);
    destroyPipeData(pipe);
}
/* 
void test_pipeEvent_given_pipe_with_AND_and_OR_module_data_should_register_event_for_all_pipe_data(void)
{
    Module *AND, *OR;
    ModuleAndPin *andData, *orData;
    Pipe *pipe;
    Node andRootNode, orNode;
    int inputType = QUAD_2_INPUT;

    AND = createdAndModule(inputType);
    OR = createdOrModule(inputType);
    pipe = createdPipeModule();
    pipe->stateToFire = HIGH;
    // storedModuleAndPin(&andData, AND, (AND->pin[0]).pinNumber);
    // storedModuleAndPin(&orData, OR, (OR->pin[1]).pinNumber);
    andData = createdModuleAndPin(AND, (AND->pin[0]).pinNumber);
    orData = createdModuleAndPin(OR, (OR->pin[1]).pinNumber);

    genericSetNode(&orNode, (void *)orData, NULL, NULL, 'r');
    genericSetNode(&andRootNode, (void *)andData, &orNode, NULL, 'b');
    pipe->data = &andRootNode;

    registerEvent_Expect(orData, NULL, ONE_NANO_SEC + OR_PROPAGATION_DELAY);
    registerEvent_Expect(andData, NULL, ONE_NANO_SEC + AND_PROPAGATION_DELAY);

    pipe->event((void *)pipe, (void *)pipe->data, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, (AND->pin[0]).state);
    TEST_ASSERT_EQUAL(HIGH, (OR->pin[1]).state);

    destroyModule(OR);
    destroyModule(AND);
    destroyPipeData(pipe);
}

void test_pipeEvent_given_pipe_with_3_module_data_should_register_event_for_all_pipe_data(void)
{
    Module *AND1, *AND2, *OR;
    ModuleAndPin *andData1, *andData2, *orData;
    Pipe *pipe;
    Node and1RootNode, and2Node, orNode;
    int inputType = QUAD_2_INPUT;

    AND1 = createdAndModule(inputType);
    AND2 = createdAndModule(inputType);
    OR = createdOrModule(inputType);
    pipe = createdPipeModule();
    pipe->stateToFire = HIGH;
    // storedModuleAndPin(&andData1, AND1, (AND1->pin[0]).pinNumber);
    andData1 = createdModuleAndPin(AND1, (AND1->pin[0]).pinNumber);
    // storedModuleAndPin(&andData2, AND2, (AND2->pin[0]).pinNumber);
    andData2 = createdModuleAndPin(AND2, (AND2->pin[0]).pinNumber);
    // storedModuleAndPin(&orData, OR, (OR->pin[1]).pinNumber);
    orData = createdModuleAndPin(OR, (OR->pin[1]).pinNumber);

    genericSetNode(&orNode, (void *)orData, NULL, NULL, 'r');
    genericSetNode(&and2Node, (void *)andData2, NULL, NULL, 'r');
    genericSetNode(&and1RootNode, (void *)andData1, &orNode, &and2Node, 'b');
    pipe->data = &and1RootNode;

    registerEvent_Expect(orData, NULL, ONE_NANO_SEC + OR_PROPAGATION_DELAY);
    registerEvent_Expect(andData2, NULL, ONE_NANO_SEC + AND_PROPAGATION_DELAY);
    registerEvent_Expect(andData1, NULL, ONE_NANO_SEC + AND_PROPAGATION_DELAY);

    pipe->event((void *)pipe, (void *)pipe->data, ONE_NANO_SEC);

    TEST_ASSERT_EQUAL(HIGH, (AND1->pin[0]).state);
    TEST_ASSERT_EQUAL(HIGH, (AND2->pin[0]).state);
    TEST_ASSERT_EQUAL(HIGH, (OR->pin[1]).state);

    destroyModule(OR);
    destroyModule(AND2);
    destroyModule(AND1);
    destroyPipeData(pipe);
}
 */