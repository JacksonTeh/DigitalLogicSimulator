#include <stdio.h>
#include "unity.h"
#include "ErrorCode.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

// #define TIME_1ns 0.0000000001
// #define TIME_2ns 500000000
// #define TIME_4ns 250000000

Node            nodeA,          nodeB,          nodeC,          nodeD;
//                |               |               |               |
//                v               v               v               v
ModuleAndPin moduleAndPin_1, moduleAndPin_2, moduleAndPin_3, moduleAndPin_4;    //dataPtr

Node       node1,    node2,    node4;
//           |         |         |
//           v         v         v
EventTime time_1ns, time_2ns, time_4ns;    //dataPtr

void setUp(void)
{
    genericResetNode(&nodeA, (void *)&moduleAndPin_1);
    genericResetNode(&nodeB, (void *)&moduleAndPin_2);
    genericResetNode(&nodeC, (void *)&moduleAndPin_3);
    genericResetNode(&nodeD, (void *)&moduleAndPin_4);

    setEventTime(&time_1ns, 1);
    setEventTime(&time_2ns, 2);
    setEventTime(&time_4ns, 4);
    genericResetNode(&node1, (void *)&time_1ns);
    genericResetNode(&node2, (void *)&time_2ns);
    genericResetNode(&node4, (void *)&time_4ns);
    // resetModuleAndPin(&moduleAndPin_1);
    // resetModuleAndPin(&moduleAndPin_2);
    // resetModuleAndPin(&moduleAndPin_3);
    // resetModuleAndPin(&moduleAndPin_4);
    // resetModuleAndPin(&moduleAndPin_5);
    // resetModuleAndPin(&moduleAndPin_6);
}

void tearDown(void)
{
}

void test_compareModuleAndPin_given_nodeA_and_nodeA_as_newNode_should_return_negative_1(void)
{
    TEST_ASSERT_EQUAL(-1, compareModuleAndPin((void *)&nodeA, (void *)&nodeA));
}

void test_compareModuleAndPin_given_nodeA_and_nodeB_as_newNode_should_return_1(void)
{
    TEST_ASSERT_EQUAL(1, compareModuleAndPin((void *)&nodeA, (void *)&nodeB));
}

void test_compareModuleAndPin_given_nodeB_and_nodeA_as_newNode_should_return_0(void)
{
    TEST_ASSERT_EQUAL(0, compareModuleAndPin((void *)&nodeB, (void *)&nodeA));
}

/** 2-node case
 *                 add A
 * root -> A(b)  -------->  Throw ERR_EQUIVALENT_NODE
 */
void test_genericAddRedBlackTree_add_nodeA_to_tree_with_only_nodeA_should_throw_ERR_EQUIVALENT_NODE(void)
{
    setNode(&nodeA, NULL, NULL, 'b');
    Node *root = &nodeA;
    CEXCEPTION_T err;

    Try{
        genericAddRedBlackTree(&root, &nodeA, compareModuleAndPin);
        TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_EQUIVALENT_NODE, err, "Expected ERR_EQUIVALENT_NODE exception");
    }
}

/** 2-node case
 *                 add A      B(b)
 * root -> B(b)  -------->   /
 *                         A(r)
 */
void test_genericAddRedBlackTree_add_nodeA_to_tree_with_only_nodeB(void)
{
    setNode(&nodeA, NULL, NULL, 'r');
    setNode(&nodeB, NULL, NULL, 'b');
    Node *root = &nodeB;

    genericAddRedBlackTree(&root, &nodeA, compareModuleAndPin);

    TEST_ASSERT_EQUAL_PTR(&nodeB, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &nodeA);
    TEST_ASSERT_EQUAL_NODE(&nodeA, NULL, 'b', &nodeB);
}

/** 2-node case
 *                 add D    C(b)
 * root -> C(b)  -------->     \
 *                             D(r)
 */
void test_genericAddRedBlackTree_add_nodeD_to_tree_with_only_nodeC(void)
{
    setNode(&nodeD, NULL, NULL, 'r');
    setNode(&nodeC, NULL, NULL, 'b');
    Node *root = &nodeC;

    genericAddRedBlackTree(&root, &nodeD, compareModuleAndPin);

    TEST_ASSERT_EQUAL_PTR(&nodeC, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &nodeD);
    TEST_ASSERT_EQUAL_NODE(NULL, &nodeD, 'b', &nodeC);
}

void test_compareEventTime_given_node1_and_node1_as_newNode_should_return_negative_1(void)
{
    TEST_ASSERT_EQUAL(-1, compareEventTime((void *)&node1, (void *)&node1));
}

void test_compareEventTime_given_node2_and_node1_as_newNode_should_return_0(void)
{
    TEST_ASSERT_EQUAL(0, compareEventTime((void *)&node2, (void *)&node1));
}

void test_compareEventTime_given_node1_and_node2_as_newNode_should_return_1(void)
{
    TEST_ASSERT_EQUAL(1, compareEventTime((void *)&node1, (void *)&node2));
}

/** 2-node case
 *                 add 1
 * root -> 1(b)  -------->  Throw ERR_EQUIVALENT_NODE
 */
void test_genericAddRedBlackTree_add_node1_to_tree_with_only_node1_should_throw_ERR_EQUIVALENT_NODE(void)
{
    setNode(&node1, NULL, NULL, 'b');
    Node *root = &node1;
    CEXCEPTION_T err;

    Try{
        genericAddRedBlackTree(&root, &node1, compareEventTime);
        TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_EQUIVALENT_NODE, err, "Expected ERR_EQUIVALENT_NODE exception");
    }
}

/** 2-node case
 *                 add 1      2(b)
 * root -> 2(b)  -------->   /
 *                         1(r)
 */
void test_genericAddRedBlackTree_add_node1_to_tree_with_only_node2(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node2, NULL, NULL, 'b');
    Node *root = &node2;

    genericAddRedBlackTree(&root, &node1, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(&node2, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node2);
}

/** 2-node case
 *                 add 4    2(b)
 * root -> 2(b)  -------->     \
 *                             4(r)
 */
void test_genericAddRedBlackTree_add_node4_to_tree_with_only_node2(void)
{
    setNode(&node4, NULL, NULL, 'r');
    setNode(&node2, NULL, NULL, 'b');
    Node *root = &node2;

    genericAddRedBlackTree(&root, &node4, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(&node2, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node4);
    TEST_ASSERT_EQUAL_NODE(NULL, &node4, 'b', &node2);
}