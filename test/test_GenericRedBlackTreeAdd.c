#include <stdio.h>
#include "unity.h"
#include "ErrorCode.h"
#include "DigitalSignalModule.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node nodeA, nodeB, nodeC, nodeD;
ModuleAndPin moduleAndPin[4];   //dataPtr

Node       node1,    node2,    node4;
//           |         |         |
//           v         v         v
EventTime time_1ns, time_2ns, time_4ns;    //dataPtr

void setUp(void)
{
    genericResetNode(&nodeA, (void *)&moduleAndPin[0]);
    genericResetNode(&nodeB, (void *)&moduleAndPin[1]);
    genericResetNode(&nodeC, (void *)&moduleAndPin[2]);
    genericResetNode(&nodeD, (void *)&moduleAndPin[3]);

    setEventTime(&time_1ns, ONE_NANO_SEC);
    setEventTime(&time_2ns, 2 * ONE_NANO_SEC);
    setEventTime(&time_4ns, 4 * ONE_NANO_SEC);
    genericResetNode(&node1, (void *)&time_1ns);
    genericResetNode(&node2, (void *)&time_2ns);
    genericResetNode(&node4, (void *)&time_4ns);
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
 *                 add A
 * root -> NULL  --------> A(b)
 */
void test_genericAddRedBlackTree_add_nodeA_to_empty_tree(void)
{
    setNode(&nodeA, NULL, NULL, 'r');
    Node *root = NULL;

    genericAddRedBlackTree(&root, &nodeA, compareModuleAndPin);

    TEST_ASSERT_EQUAL_PTR(&nodeA, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &nodeA);
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
 * root -> NULL  --------> 1(b)
 */
void test_genericAddRedBlackTree_add_node1_to_empty_tree(void)
{
    setNode(&node1, NULL, NULL, 'r');
    Node *root = NULL;

    genericAddRedBlackTree(&root, &node1, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(&node1, root);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
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