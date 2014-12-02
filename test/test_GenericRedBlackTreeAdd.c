#include <stdio.h>
#include "unity.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

ModuleAndPin moduleAndPin_1, moduleAndPin_2, moduleAndPin_3, moduleAndPin_4, moduleAndPin_5,  moduleAndPin_6;

void setUp(void)
{
    resetModuleAndPin(&moduleAndPin_1);
    resetModuleAndPin(&moduleAndPin_2);
    resetModuleAndPin(&moduleAndPin_3);
    resetModuleAndPin(&moduleAndPin_4);
    resetModuleAndPin(&moduleAndPin_5);
    resetModuleAndPin(&moduleAndPin_6);
}

void tearDown(void)
{
}

/** Empty node case
 *                add moduleAndPin_1
 * root -> NULL  ------------------->  1(b)  <- root
 */
void test_genericAddRedBlackTree_add_moduleAndPin_1_to_empty_tree(void)
{
    setModuleAndPin(&moduleAndPin_1, NULL, NULL, 'r');
    ModuleAndPin *root = NULL;
    int typeOfRBT = MODULE_AND_PIN;

    genericAddRedBlackTree((void *)&root, (void *)&moduleAndPin_1, typeOfRBT);

    TEST_ASSERT_EQUAL_PTR(&moduleAndPin_1, root);
    TEST_ASSERT_EQUAL_MODULE_AND_PIN(NULL, NULL, 'b', &moduleAndPin_1);
}

/** 2-node case
 *                 add moduleAndPin_1
 * root -> 1(b)  ---------------------> Throw ERR_EQUIVALENT_NODE
 */
void xtest_addRedBlackTree_add_moduleAndPin_1_to_use_tree_with_only_moduleAndPin_1_should_throw_ERR_EQUIVALENT_NODE(void)
{
    CEXCEPTION_T err;
    setModuleAndPin(&moduleAndPin_1, NULL, NULL, 'b');
    ModuleAndPin *root = &moduleAndPin_1;
    int typeOfRBT = MODULE_AND_PIN;

    Try{
        genericAddRedBlackTree((void *)&root, (void *)&moduleAndPin_1, typeOfRBT);
        TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_PTR(root, &moduleAndPin_1);
        TEST_ASSERT_EQUAL_MODULE_AND_PIN(NULL, NULL, 'b', &moduleAndPin_1);
    }
}

