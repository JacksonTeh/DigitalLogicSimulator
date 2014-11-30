#include <stdio.h>
#include "unity.h"
#include "RedBlackTree.h"
#include "InitNode.h"
#include "CustomAssertions.h"
#include "Rotations.h"
#include "CException.h"

Node node1, node3, node5, node6, node7, node8, node10, node13, node15, node17, node20, node25, node30, node40;

void setUp(void)
{
    resetNode(&node1, 1);
    resetNode(&node3, 3);
    resetNode(&node5, 5);
    resetNode(&node6, 6);
    resetNode(&node7, 7);
    resetNode(&node8, 8);
    resetNode(&node10, 10);
    resetNode(&node13, 13);
    resetNode(&node15, 15);
    resetNode(&node17, 17);
    resetNode(&node20, 20);
    resetNode(&node25, 25);
    resetNode(&node30, 30);
    resetNode(&node40, 40);
}

void tearDown(void)
{
}

/** Empty node case
 *                add 10
 * root -> NULL  ------->  10(b)  <- root
 */
void test_addRedBlackTree_add_10_to_empty_tree(void)
{
    setNode(&node10, NULL, NULL, 'r');
    Node *root = NULL;

    addRedBlackTree(&root, &node10);

    TEST_ASSERT_EQUAL_PTR(root, &node10);
    //                     left right colour  node
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    // TEST_ASSERT_EQUAL('b', node10.colour);
    // TEST_ASSERT_EQUAL_PTR(NULL, node10.left);
    // TEST_ASSERT_EQUAL_PTR(NULL, node10.right);
}

/** 2-node case
 *                 add 10
 * root -> 10(b)  -------> Throw ERR_EQUIVALENT_NODE
 */
void test_addRedBlackTree_add_10_to_use_tree_with_only_root_10_should_throw_ERR_EQUIVALENT_NODE(void)
{
    CEXCEPTION_T err;
    setNode(&node10, NULL, NULL, 'b');
    Node *root = &node10;

    Try{
        addRedBlackTree(&root, &node10);
        TEST_FAIL_MESSAGE("Expected ERR_EQUIVALENT_NODE to be thrown. But receive none");
    } Catch(err)
    {
        TEST_ASSERT_EQUAL_PTR(&node10, root);
        //                      left  right colour  node
        TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node10);
    }
}

/** 2-node case
 *                 add 5
 * root -> 10(b)  ------->   10(b)  <- root
 *                           /
 *                         5(r)
 */
void test_addRedBlackTree_add_5_to_use_tree_with_only_root_10(void)
{
    setNode(&node10, NULL, NULL, 'b');
    setNode(&node5, NULL, NULL, 'r');
    Node *root = &node10;

    addRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node10, root);
    //                      left  right colour  node
    TEST_ASSERT_EQUAL_NODE(&node5, NULL, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
}

/** 2-node case
 *                 add 15
 * root -> 10(b)  ------->   10(b)  <- root
 *                              \
 *                             15(r)
 */
void test_addRedBlackTree_add_15_to_use_tree_with_only_root_10(void)
{
    setNode(&node10, NULL, NULL, 'b');
    setNode(&node15, NULL, NULL, 'r');
    Node *root = &node10;

    addRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, &node15, 'b', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node15);
}

/** 3-node case
 *                               10(b)  <- root
 * root -> 10(b)   add 1         /                            5(b)   <- root
 *         /      ------->    5(r)              ------>      /   \
 *      5(r)                  /                           1(r)  10(r)
 *                          1(r)
 */
void test_addRedBlackTree_add_1_to_use_tree_with_root_10(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(&node5, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node5);
}

/** 3-node case
 *                               10(b)  <- root
 * root -> 10(b)   add 7         /                            7(b)   <- root
 *         /      ------->    5(r)              ------>      /   \
 *      5(r)                    \                           5(r)  10(r)
 *                             7(r)
 */
void test_addRedBlackTree_add_7_to_use_tree_with_root_10(void)
{
    setNode(&node7, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(&node7, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(&node5, &node10, 'b', &node7);
}

/** 3-node case
 * root -> 10(b)   add 20      10(b)  <- root
 *         /      ------->    /   \
 *      5(r)               5(r)  20(r)
 */
void test_addRedBlackTree_add_20_to_use_tree_with_root_10(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node20);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
}

/** 3-node case
 *                             10(b)  <- root
 * root -> 10(b)    add 30        \                      20(b)   <- root
 *            \    ------->      20(r)        ------>    /   \
 *           20(r)                  \                 10(r)  30(r)
 *                                 30(r)
 */
void test_addRedBlackTree_add_30_to_use_tree_with_root_10(void)
{
    setNode(&node30, NULL, NULL, 'r');
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node30);

    TEST_ASSERT_EQUAL_PTR(&node20, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node30);
    TEST_ASSERT_EQUAL_NODE(&node10, &node30, 'b', &node20);
}

/** 3-node case
 *                             10(b)  <- root
 * root -> 10(b)    add 15        \                       15(b)   <- root
 *            \    ------->      20(r)        ------>    /   \
 *           20(r)               /                    10(r)  20(r)
 *                            15(r)
 */
void test_addRedBlackTree_add_15_to_use_tree_with_root_10(void)
{
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node15);

    TEST_ASSERT_EQUAL_PTR(&node15, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node10, &node20, 'b', &node15);
}

/** 3-node case
 * root -> 10(b)    add 5       10(b)  <- root
 *            \    ------->    /   \
 *           20(r)           5(r)  20(r)
 */
void test_addRedBlackTree_add_5_to_use_tree_with_root_10(void)
{
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    addRedBlackTree(&root, &node5);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(&node5, &node20, 'b', &node10);
}

/** 4-node case
 *                               10(b)  <- root            10(b)  <- root           10(r)  <- root
 * root -> 10(b)     add 1       /   \                     /   \                    /   \
 *         /   \    ------->   5(r)  15(r)      ----->   5(b)  15(b)      ----->  5(b)  15(b)
 *       5(r) 15(r)            /                         /                        /
 *                           1(r)                      1(r)                     1(r)
 */
void test_addRedBlackTree_add_1_to_use_tree_with_5_10_15_nodes(void)
{
    setNode(&node1, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    _addRedBlackTree(&root, &node1);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node1);
    TEST_ASSERT_EQUAL_NODE(&node1, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
}

/** 4-node case
 *                               10(b)  <- root            10(b)  <- root           10(r)  <- root
 * root -> 10(b)     add 7       /   \                     /   \                    /   \
 *         /   \    ------->   5(r)  15(r)      ----->   5(b)  15(b)      ----->  5(b)  15(b)
 *       5(r) 15(r)               \                         \                        \
 *                               7(r)                      7(r)                     7(r)
 */
void test_addRedBlackTree_add_7_to_use_tree_with_5_10_15_nodes(void)
{
    setNode(&node7, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    _addRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
}

/** 4-node case
 *                               10(b)  <- root            10(b)  <- root           10(r)  <- root
 * root -> 10(b)     add 13      /   \                     /   \                    /   \
 *         /   \    ------->   5(r)  15(r)      ----->   5(b)  15(b)      ----->  5(b)  15(b)
 *       5(r) 15(r)                  /                         /                        /
 *                                 13(r)                     13(r)                    13(r)
 */
void test_addRedBlackTree_add_13_to_use_tree_with_5_10_15_nodes(void)
{
    setNode(&node13, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    _addRedBlackTree(&root, &node13);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node13);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(&node13, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
}

/** 4-node case
 *                               10(b)  <- root            10(b)  <- root           10(r)  <- root
 * root -> 10(b)     add 20      /   \                     /   \                    /   \
 *         /   \    ------->   5(r)  15(r)      ----->   5(b)  15(b)      ----->  5(b)  15(b)
 *       5(r) 15(r)                     \                         \                        \
 *                                     20(r)                     20(r)                    20(r)
 */
void test_addRedBlackTree_add_20_to_use_tree_with_5_10_15_nodes(void)
{
    setNode(&node20, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    _addRedBlackTree(&root, &node20);

    TEST_ASSERT_EQUAL_PTR(&node10, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node20);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, &node20, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
}

/** 4-node case
 * root -> 20(b)                 20(b)  <- root            20(b)  <- root
 *         /   \     add 7       /   \                     /   \
 *      10(b) 25(b) ------->  10(b) 25(b)      ----->   10(r) 25(b)
 *      /   \                 /   \                     /   \
 *    5(r) 15(r)            5(r) 15(r)                5(b) 15(b)
 *                             \                         \
 *                            7(r)                      7(r)
 */
void test_addRedBlackTree_add_7_to_use_tree_with_5_10_15_20_25_nodes(void)
{
    setNode(&node7, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    setNode(&node25, NULL, NULL, 'b');
    setNode(&node20, &node10, &node25, 'b');
    Node *root = &node20;

    addRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(&node20, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node25);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(&node10, &node25, 'b', &node20);
}

/** 4-node case
 * root ->     20(b)                             20(b)  <- root                    20(b)  <- root                     20(b)  <- root
 *         /          \                      /          \                      /          \                       /          \
 *       3(r)        30(r)                 3(r)        30(r)                 3(r)        30(r)                  3(b)        30(b)
 *      /   \        /   \       add 7    /   \        /   \                /   \        /   \                 /   \        /   \
 *    1(b) 10(b)  25(b) 40(b)  -------> 1(b) 10(b)  25(b) 40(b)  -------> 1(b) 10(b)  25(b) 40(b)  ------->  1(b) 10(r)  25(b) 40(b)
 *         /   \                             /   \                             /   \                              /   \
 *       5(r) 15(r)                        5(r) 15(r)                        5(b) 15(b)                         5(b) 15(b)
 *                                            \                                 \                                  \
 *                                           7(r)                              7(r)                               7(r)
 */
void test_addRedBlackTree_add_7_to_use_tree_with_1_4_5_10_15_20_25_30_40_nodes(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'r');
    setNode(&node5, NULL, NULL, 'r');
    setNode(&node15, NULL, NULL, 'r');
    setNode(&node10, &node5, &node15, 'b');
    setNode(&node3, &node1, &node10, 'r');
    setNode(&node25, NULL, NULL, 'b');
    setNode(&node40, NULL, NULL, 'b');
    setNode(&node30, &node25, &node40, 'r');
    setNode(&node20, &node3, &node30, 'b');
    Node *root = &node20;

    addRedBlackTree(&root, &node7);

    TEST_ASSERT_EQUAL_PTR(&node20, root);

    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node1);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'r', &node7);
    TEST_ASSERT_EQUAL_NODE(NULL, &node7, 'b', &node5);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node15);
    TEST_ASSERT_EQUAL_NODE(&node5, &node15, 'r', &node10);
    TEST_ASSERT_EQUAL_NODE(&node1, &node10, 'b', &node3);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node25);
    TEST_ASSERT_EQUAL_NODE(NULL, NULL, 'b', &node40);
    TEST_ASSERT_EQUAL_NODE(&node25, &node40, 'b', &node30);
    TEST_ASSERT_EQUAL_NODE(&node3, &node30, 'b', &node20);
}