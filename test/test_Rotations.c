#include "unity.h"
#include "Node.h"
#include "Rotations.h"
#include "InitNode.h"

Node node1, node5, node6, node7, node8, node10, node13, node15, node17, node20, node30;

/* void setNode(Node *target, Node *left, Node *right, char colour)
{
    target->left = left;
    target->right = right;
    target->colour = colour;
}

void resetNode(Node *target, int data)
{
    target->left = NULL;
    target->right = NULL;
    target->colour = 'b';
    target->data = data;
} */

void setUp(void)
{
    resetNode(&node1, 1);
    resetNode(&node5, 5);
    resetNode(&node6, 6);
    resetNode(&node7, 7);
    resetNode(&node8, 8);
    resetNode(&node10, 10);
    resetNode(&node13, 13);
    resetNode(&node15, 15);
    resetNode(&node17, 17);
    resetNode(&node20, 20);
    resetNode(&node30, 30);
}

void tearDown(void)
{
}

void changeRootByVal(Node *node, Node *newNode)
{
    node = newNode;
    printf("changeRootByVal: node = %x\n", node);
}

void changeRootByRef(Node **nodePtr, Node *newNode)
{
    *nodePtr = newNode;
    printf("changeRootByRef: node = %x\n", *nodePtr);
}

void xtest_changeRootByVal()
{
    Node *root;
    root = &node10;

    printf("test_changeRootByVal\n");
    printf("--------------------\n");
    printf("root is node %d with address %x\n", root->data, root);
    changeRootByVal(root, &node5);
    printf("root is node %d with address %x\n\n", root->data, root);
}

void xtest_changeRootByRef()
{
    Node *root;
    root = &node10;

    printf("test_changeRootByRef\n");
    printf("--------------------\n");
    printf("root is node %d with address %x\n", root->data, root);
    changeRootByRef(&root, &node5);
    printf("root is node %d with address %x\n\n", root->data, root);
}

/**
 * root ->  10
 *         /                5  <- root
 *        5     --->      /  \
 *       /               1    10
 *      1
 */
void test_rightRotate_given_parent_and_two_left_childs_should_rotate_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, NULL, 'b');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    rightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/**
 * root ->  10               5  <- root
 *         /  \            /  \
 *        5   15  --->    1   10
 *       /                      \
 *      1                       15
 */
void test_rightRotate_given_parent_and_two_left_childs_one_right_child_should_rotate_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node5, &node1, NULL, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    rightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
    TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/**
 * root ->  10               5  <- root
 *         /  \            /  \
 *        5   15  --->    1   10
 *       / \                 /  \
 *      1   7               7   15
 */
void test_rightRotate_given_parent_and_three_left_childs_one_right_child_should_rotate_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    rightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node7.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node7.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node7);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
    TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node5);
}

/**
 * root ->  10
 *            \              15  <- root
 *            15    --->    /  \
 *             \          10    20
 *             20
 */
void test_leftRotate_given_parent_and_two_right_childs_should_rotate_left(void)
{
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, NULL, &node20, 'b');
    setNode(&node10, NULL, &node15, 'b');
    Node *root = &node10;

    leftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 * root ->  10               15  <- root
 *         /  \             /  \
 *        5   15   --->   10    20
 *             \         /
 *             20       5
 */
void test_leftRotate_given_parent_and_two_right_childs_and_one_left_child_should_rotate_left(void)
{
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node15, NULL, &node20, 'b');
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    leftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 * root ->  10               15  <- root
 *         /  \             /  \
 *        5   15   --->   10    20
 *           /  \        /  \
 *         13   20      5   13
 */
void test_leftRotate_given_parent_and_three_right_childs_and_one_left_child_should_rotate_left(void)
{
    setNode(&node20, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node15, &node13, &node20, 'b');
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    leftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node13.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node13.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node13);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 * root ->  10            10
 *         /             /                7  <- root
 *        5      --->   7     --->      /  \
 *         \           /               5    10
 *          7         5
 */
void test_leftRightRotate_given_parent_and_two_left_childs_should_rotate_left_then_right(void)
{
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, NULL, &node7, 'b');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    leftRightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node7);
}

/**
 *                         10
 *                         /
 * root ->  10            7               7  <- root
 *         /             /              /  \
 *        5      --->   5     --->     5    10
 *      /  \           /              /
 *     1    7         1              1
 */
void test_leftRightRotate_given_parent_and_three_left_childs_should_rotate_left_then_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node7, NULL, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node10, &node5, NULL, 'b');
    Node *root = &node10;

    leftRightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node7);
}

/**
 * root ->  10                10
 *         /  \              /  \
 *        5   15            7   15               7  <- root
 *      /  \               / \                 /   \
 *     1    7      --->   5   8       --->    5    10
 *           \           /                   /    /  \
 *            8         1                   1    8   15
 */
void test_leftRightRotate_given_parent_and_four_left_childs_and_one_right_child_should_rotate_left_then_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node8, NULL, NULL, 'b');
    setNode(&node7, NULL, &node8, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    leftRightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node8.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node8.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node8);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
    TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node7);
}

/**
 * root ->  10                10
 *         /  \              /  \
 *        5   15            7   15               7  <- root
 *      /  \               /                   /   \
 *     1    7      --->   5           --->    5    10
 *         /             / \                 / \     \
 *        6             1   6               1   6    15
 */
void test_leftRightRotate_given_parent_with_different_four_left_childs_and_one_right_child_should_rotate_left_then_right(void)
{
    setNode(&node1, NULL, NULL, 'b');
    setNode(&node6, NULL, NULL, 'b');
    setNode(&node7, &node6, NULL, 'b');
    setNode(&node5, &node1, &node7, 'b');
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node10, &node5, &node15, 'b');
    Node *root = &node10;

    leftRightRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node1.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node1.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node6.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node6.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.left, &node1);
    TEST_ASSERT_EQUAL_PTR(node5.right, &node6);
    TEST_ASSERT_EQUAL_PTR(node15.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node15);
    TEST_ASSERT_EQUAL_PTR(node7.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node7.right, &node10);
    TEST_ASSERT_EQUAL_PTR(root, &node7);
}

/**
 * root ->  10            10
 *            \            \                 15  <- root
 *            20  --->     15     --->      /  \
 *           /              \             10   20
 *          15              20
 */
void test_rightLeftRotate_given_parent_and_two_right_childs_should_rotate_right_then_left(void)
{
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node20, &node15, NULL, 'b');
    setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    rightLeftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 *                         10
 *                          \
 * root ->   10             15              15   <- root
 *            \              \             /  \
 *            20    --->     20   --->   10   20
 *           /  \             \                 \
 *          15  30            30                30
 */
void test_rightLeftRotate_given_parent_and_three_right_childs_should_rotate_right_then_left(void)
{
    setNode(&node15, NULL, NULL, 'b');
    setNode(&node30, NULL, NULL, 'b');
    setNode(&node20, &node15, &node30, 'b');
    setNode(&node10, NULL, &node20, 'b');
    Node *root = &node10;

    rightLeftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
    TEST_ASSERT_EQUAL_PTR(node10.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 * root ->   10              10
 *          /  \            / \
 *         5   20          5  15              15   <- root
 *            /  \           / \             /  \
 *           15  30  --->  13  20   --->   10   20
 *          /                   \         /  \   \
 *         13                   30       5   13  30
 */
void test_rightLeftRotate_given_parent_and_four_right_childs_and_one_left_child_should_rotate_right_then_left(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node13, NULL, NULL, 'b');
    setNode(&node15, &node13, NULL, 'b');
    setNode(&node30, NULL, NULL, 'b');
    setNode(&node20, &node15, &node30, 'b');
    setNode(&node10, &node5, &node20, 'b');
    Node *root = &node10;

    rightLeftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node13.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node13.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node10.right, &node13);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}

/**
 * root ->   10              10
 *          /  \            / \
 *         5   20          5  15              15   <- root
 *            /  \             \             /  \
 *           15  30  --->      20   --->   10   20
 *            \               / \         /    / \
 *            17             17 30       5    17 30
 */
void test_rightLeftRotate_given_parent_with_four_right_childs_and_one_left_child_should_rotate_right_then_left(void)
{
    setNode(&node5, NULL, NULL, 'b');
    setNode(&node17, NULL, NULL, 'b');
    setNode(&node15, NULL, &node17, 'b');
    setNode(&node30, NULL, NULL, 'b');
    setNode(&node20, &node15, &node30, 'b');
    setNode(&node10, &node5, &node20, 'b');
    Node *root = &node10;

    rightLeftRotate(&root);

    TEST_ASSERT_EQUAL_PTR(node5.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node5.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node17.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node17.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node30.left, NULL);
    TEST_ASSERT_EQUAL_PTR(node30.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node20.left, &node17);
    TEST_ASSERT_EQUAL_PTR(node20.right, &node30);
    TEST_ASSERT_EQUAL_PTR(node10.left, &node5);
    TEST_ASSERT_EQUAL_PTR(node10.right, NULL);
    TEST_ASSERT_EQUAL_PTR(node15.left, &node10);
    TEST_ASSERT_EQUAL_PTR(node15.right, &node20);
    TEST_ASSERT_EQUAL_PTR(root, &node15);
}