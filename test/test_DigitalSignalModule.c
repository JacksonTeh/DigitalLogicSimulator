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

    andModule = createdAndModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(andModule);
    TEST_ASSERT_EQUAL(1, andModule->input1a);
    TEST_ASSERT_EQUAL(0, andModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&andEvent, andModule->event);
    TEST_ASSERT_EQUAL_PTR(&setAnd, andModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, andModule->configure);
	// printf("yes\n");
    destroyModule(andModule);
}

void test_createdOrModule_should_create_module_for_OR_gate(void)
{
    Module *orModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    orModule = createdOrModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(orModule);
    TEST_ASSERT_EQUAL(1, orModule->input1a);
    TEST_ASSERT_EQUAL(0, orModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&orEvent, orModule->event);
    TEST_ASSERT_EQUAL_PTR(&setOr, orModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, orModule->configure);

    destroyModule(orModule);
}

void test_createdXorModule_should_create_module_for_XOR_gate(void)
{
    Module *xorModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    xorModule = createdXorModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(xorModule);
    TEST_ASSERT_EQUAL(1, xorModule->input1a);
    TEST_ASSERT_EQUAL(0, xorModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&xorEvent, xorModule->event);
    TEST_ASSERT_EQUAL_PTR(&setXor, xorModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, xorModule->configure);

    destroyModule(xorModule);
}

void test_createdNandModule_should_create_module_for_NAND_gate(void)
{
    Module *nandModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    nandModule = createdNandModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(nandModule);
    TEST_ASSERT_EQUAL(1, nandModule->input1a);
    TEST_ASSERT_EQUAL(0, nandModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&nandEvent, nandModule->event);
    TEST_ASSERT_EQUAL_PTR(&setNand, nandModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, nandModule->configure);

    destroyModule(nandModule);
}

void test_createdNorModule_should_create_module_for_NOR_gate(void)
{
    Module *norModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    norModule = createdNorModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(norModule);
    TEST_ASSERT_EQUAL(1, norModule->input1a);
    TEST_ASSERT_EQUAL(0, norModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&norEvent, norModule->event);
    TEST_ASSERT_EQUAL_PTR(&setNor, norModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, norModule->configure);

    destroyModule(norModule);
}

void test_createdNotModule_should_create_module_for_NOT_gate(void)
{
    Module *notModule;
    Inbit input1a = 1;
    Inbit input2a = 0;

    notModule = createdNotModule(NULL, input1a, input2a);

    TEST_ASSERT_NOT_NULL(notModule);
    TEST_ASSERT_EQUAL(1, notModule->input1a);
    TEST_ASSERT_EQUAL(0, notModule->input2a);
    TEST_ASSERT_EQUAL_PTR(&notEvent, notModule->event);
    TEST_ASSERT_EQUAL_PTR(&setNot, notModule->set);
    TEST_ASSERT_EQUAL_PTR(&configureInputOutput, notModule->configure);

    destroyModule(notModule);
}