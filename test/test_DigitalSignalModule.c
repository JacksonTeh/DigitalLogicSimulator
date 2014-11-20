#include <malloc.h>
#include "unity.h"
#include "DigitalSignalModule.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createdAndModule_should_create_module_for_AND_gate(void)
{
    Module *andModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    andModule = createdAndModule(input1a, input2a);

    TEST_ASSERT_NOT_NULL(andModule);
    TEST_ASSERT_EQUAL(1, andModule->input1a);
    TEST_ASSERT_EQUAL(0, andModule->input2a);
	// printf("yes\n");
    destroyModule(andModule);
}
