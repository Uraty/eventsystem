#include "unity.h"
#include "ordered-event.h"
#include "dsl.h"
#include "utils.h"

int callCounter;
int lastCallId;
void call1()
{
	lastCallId = ++callCounter * 10 + 1;
}
void call2()
{
	lastCallId = ++callCounter * 10 + 2;
}

void setUp()
{
	lastCallId = callCounter = 0;
}

OrderedEvent(OEvent1, 2, defaultGroup)
{
    bindListener(call1);
}
OrderedEvent(OEvent2, 2, defaultGroup)
{
    bindListener(call2);
}

void test_ordering()
{
    // ev1 - 1
	publishEvent(OEvent1);

    // ev2 - 2
	publishEvent(OEvent2);

    // ev3 - 2
	publishEvent(OEvent2);

    // ev4 - 1
	publishEvent(OEvent1);

    // ev5 -2  - no more place
	publishEvent(OEvent2);


    // ev1 - 1
	handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(0, lastCallId);
    handleEvent(OEvent1);
	TEST_ASSERT_EQUAL(11, lastCallId);

    // ev2 - 2
    handleEvent(OEvent1);
	TEST_ASSERT_EQUAL(11, lastCallId);
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(22, lastCallId);

    // ev3 - 2
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(32, lastCallId);

    // ev4 - 1
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(32, lastCallId);
    handleEvent(OEvent1);
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev4 - 2 - no more place
    handleEvent(OEvent1);
    TEST_ASSERT_EQUAL(41, lastCallId);
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(41, lastCallId);

    // ev6 - 2
	publishEvent(OEvent2);

     // ev7 - 1
	publishEvent(OEvent1);

    // ev6 - 2
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(52, lastCallId);

    // ev7 - 1
    handleEvent(OEvent2);
	TEST_ASSERT_EQUAL(52, lastCallId);
    handleEvent(OEvent1);
    TEST_ASSERT_EQUAL(61, lastCallId);
}
