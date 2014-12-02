#include "unity.h"
#include "CustomAssertions.h"

/**
 * Custom assertions of red-black tree
 */
void assertNode(Node *left, Node *right, char colour, Node *actualNode, int lineNumber)
{            //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ ^^^^^^^^^^^^^^^^
             //             expected constant              actual
    UNITY_TEST_ASSERT_EQUAL_INT8(colour, actualNode->colour, lineNumber, "Wrong colour");
    UNITY_TEST_ASSERT_EQUAL_PTR(left, actualNode->left, lineNumber, "Wrong left node");
    UNITY_TEST_ASSERT_EQUAL_PTR(right, actualNode->right, lineNumber, "Wrong right node");
}

void assertModuleAndPin(ModuleAndPin *left, ModuleAndPin *right, char colour, ModuleAndPin *actualModuleAndPin, int lineNumber)
{
    UNITY_TEST_ASSERT_EQUAL_INT8(colour, actualModuleAndPin->colour, lineNumber, "Wrong colour");
    UNITY_TEST_ASSERT_EQUAL_PTR(left, actualModuleAndPin->left, lineNumber, "Wrong left node");
    UNITY_TEST_ASSERT_EQUAL_PTR(right, actualModuleAndPin->right, lineNumber, "Wrong right node");
}