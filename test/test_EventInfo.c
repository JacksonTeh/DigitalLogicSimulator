#include "unity.h"
#include "EventInfo.h"
// #include "DigitalEventSimulator.h"
#include "InitNode.h"
#include "RedBlackTree.h"
#include "Rotations.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createdEventInfo_should_create_EventInfo_with_moduleAndPin_and_pipe(void)
{
    ModuleAndPin moduleAndPin;
    Pipe pipe;
    EventInfo *eventInfo = createdEventInfo(&moduleAndPin, &pipe);

    TEST_ASSERT_NOT_NULL(eventInfo);
    TEST_ASSERT_EQUAL_PTR(&moduleAndPin, eventInfo->moduleAndPin);
    TEST_ASSERT_EQUAL_PTR(&pipe, eventInfo->pipe);

    destroyEventInfo(eventInfo);
}
