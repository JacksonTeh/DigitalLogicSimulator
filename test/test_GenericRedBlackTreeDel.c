#include <stdio.h>
#include "unity.h"
#include "ErrorCode.h"
#include "DigitalSignalModule.h"
#include "DigitalEventSimulator.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

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
}

void tearDown(void)
{
}

/** 2-node case
 *                remove 2
 * root -> 1(b)  --------->  Throw ERR_NODE_UNAVAILABLE
 */
void test_genericDelRedBlackTree_remove_node2_from_tree_with_only_node1_should_throw_ERR_NODE_UNAVAILABLE(void)
{
    setNode(&node2, NULL, NULL, 'r');
    setNode(&node1, NULL, NULL, 'b');
    Node *root = &node1;
    CEXCEPTION_T err;

    Try{
        genericDelRedBlackTree(&root, &node2, compareEventTime);
        TEST_FAIL_MESSAGE("Expected ERR_NODE_UNAVAILABLE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_MESSAGE(ERR_NODE_UNAVAILABLE, err, "Expected ERR_NODE_UNAVAILABLE exception");
    }
}

/** 2-node case
 *                remove 2
 * root -> 2(b)  ----------> NULL
 */
void test_genericDelRedBlackTree_remove_node2_from_tree_with_only_node2(void)
{
    setNode(&node2, NULL, NULL, 'b');
    Node *root = &node2, *removeNode;

    removeNode = genericDelRedBlackTree(&root, &node2, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(NULL, root);
    TEST_ASSERT_EQUAL_PTR(&node2, removeNode);
}

/** 2-node case
 *
 * root -> 2(b)   remove 1
 *        /      ---------->  2(b) <- root
 *      1(r)
 */
void test_genericDelRedBlackTree_remove_node1_from_tree_with_node_1_2(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node2, &node1, NULL, 'b');
    Node *root = &node2, *removeNode;

    removeNode = genericDelRedBlackTree(&root, &node1, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(&node2, root);
    TEST_ASSERT_EQUAL_PTR(&node1, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node2);
}

/** 2-node case
 *
 * root -> 2(b)    remove 4
 *            \   ---------->  4(b) <- root
 *           4(r)
 */
void test_genericDelRedBlackTree_remove_node2_from_tree_with_node_2_4(void)
{
    setNode(&node4, NULL, NULL, 'r');
    setNode(&node2, NULL, &node4, 'b');
    Node *root = &node2, *removeNode;

    removeNode = genericDelRedBlackTree(&root, &node2, compareEventTime);

    TEST_ASSERT_EQUAL_PTR(&node4, root);
    TEST_ASSERT_EQUAL_PTR(&node2, removeNode);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node4);
}