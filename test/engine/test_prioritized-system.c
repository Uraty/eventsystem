#include "unity.h"
#include "event.h"
#include "dsl.h"
#include "utils.h"

#include "prioritized-system.h"

int eventsCounter;
int orderOfEvents[10];

void happened(int id)
{
	orderOfEvents[eventsCounter++] = id;
}

Event(HighEvent, 3)
{
	happened(1);
}
Event(MediumEvent, 3)
{
	happened(2);
}
Event(LowEvent, 3)
{
	happened(3);
}

EventSystem
{
	HighestPriority
	{
		registerEvent(HighEvent);
	}
	MediumPriority
	{
		registerEvent(MediumEvent);
	}
	LowPriority
	{
		registerEvent(LowEvent);
	}
}

void test_array()
{
	repeat(3) publishEvent(LowEvent);
	repeat(3) publishEvent(MediumEvent)
	repeat(4) publishEvent(HighEvent)


	_evs_systemStep();

	int expectedOrderOfEvents1[] = { 1, 1, 1, 2, 2, 2, 3, 0, 0, 0 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents1, orderOfEvents, 10);


	_evs_systemStep();

	int expectedOrderOfEvents2[] = { 1, 1, 1, 2, 2, 2, 3, 3, 0, 0 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents2, orderOfEvents, 10);


	publishEvent(HighEvent)
	_evs_systemStep();

	int expectedOrderOfEvents3[] = { 1, 1, 1, 2, 2, 2, 3, 3, 1, 3 };
	TEST_ASSERT_EQUAL_INT_ARRAY(expectedOrderOfEvents3, orderOfEvents, 10);
}

