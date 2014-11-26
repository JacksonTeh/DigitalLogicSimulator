#include <malloc.h>
#include <stdio.h>
#include "unity.h"
#include "DigitalSignalModule.h"
#include "CException.h"
#include "mock_DigitalEventSimulator.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createdAndModule_given_1_number_of_input_pin_should_throw_ERR_INVALID_PIN_NUMBER(void)
{
    CEXCEPTION_T err;
    Module *AND;
    int numberOfPin = 1;

    Try{
        AND = createdAndModule(numberOfPin);
        TEST_FAIL_MESSAGE("Expected ERR_INVALID_PIN_NUMBER to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL(ERR_INVALID_PIN_NUMBER, err);
		printf("Success: Exception generated. Error code: %d.\n", err);
    }
}

void test_createdAndModule_given_2_number_of_input_pin_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int numberOfPin = 2;

    AND = createdAndModule(numberOfPin);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[0]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[1]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->output[0]);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);
	// printf("yes\n");
    destroyModule(AND);
}

void test_createdAndModule_given_4_number_of_input_pin_should_create_module_for_AND_gate(void)
{
    Module *AND;
    int numberOfPin = 4;

    AND = createdAndModule(numberOfPin);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[0]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[1]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[2]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->input[3]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->output[0]);
    TEST_ASSERT_EQUAL(UNKNOWN, AND->output[1]);
    TEST_ASSERT_EQUAL_PTR(&andEvent, AND->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, AND->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, AND->configure);

    destroyModule(AND);
}

void test_createdNotModule_given_3_number_of_input_pin_should_create_module_for_NOT_gate(void)
{
    Module *NOT;
    int numberOfPin = 3;

    NOT = createdNotModule(numberOfPin);

    TEST_ASSERT_NOT_NULL(NOT);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->input[0]);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->input[1]);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->input[2]);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->output[0]);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->output[1]);
    TEST_ASSERT_EQUAL(UNKNOWN, NOT->output[2]);
    TEST_ASSERT_EQUAL_PTR(&notEvent, NOT->event);
    TEST_ASSERT_EQUAL_PTR(&setNot, NOT->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, NOT->configure);

    destroyModule(NOT);
}

void test_configureInputOutput_given_AND_and_OR_should_connect_output_from_OR_to_AND(void)
{
    Module *AND;
    Module *OR;
    int numberOfOrPin = 4, numberOfAndPin = 2, orOutPin = 2, andInPin = 1;

    OR = createdOrModule(numberOfOrPin);
    AND = createdAndModule(numberOfAndPin);

    OR->configure((void *)OR, (void *)orOutPin, (void *)AND, (void *)andInPin);

    TEST_ASSERT_NOT_NULL(AND);
    TEST_ASSERT_NOT_NULL(OR);
    // TEST_ASSERT_EQUAL(&AND->input[0], &OR->output[1]);

    destroyModule(AND);
    destroyModule(OR);
}