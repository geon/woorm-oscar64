#include "circular-buffer.h"
#include "test/test.h"

CircularBuffer circularBuffer;
Direction circularBufferValues[0x100];

void circularBufferTest()
{
	beginTest("Create circularBuffer.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);
	}
	endTest();

	beginTest("Push element to circularBuffer.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);

		circularBufferPush(&circularBuffer, Direction_up);
	}
	endTest();

	beginTest("Pop element from circularBuffer.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);

		circularBufferPush(&circularBuffer, Direction_up);
		circularBufferPop(&circularBuffer);
	}
	endTest();

	beginTest("Push and pop element.");
	{
		// Can't for-loop over 256 element with a byte counter.
		for (int i = 0x00; i <= 0xff; ++i)
		{
			circularBufferInit(&circularBuffer, circularBufferValues);

			Direction pushed = i % Direction_count;
			circularBufferPush(&circularBuffer, pushed);
			Direction popped = circularBufferPop(&circularBuffer);

			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();

	beginTest("Push and pop 2 elements.");
	{

		circularBufferInit(&circularBuffer, circularBufferValues);

		Direction firstPushed = Direction_up;
		circularBufferPush(&circularBuffer, firstPushed);
		Direction secondPushed = Direction_down;
		circularBufferPush(&circularBuffer, secondPushed);

		Direction firstPopped = circularBufferPop(&circularBuffer);
		Direction secondPopped = circularBufferPop(&circularBuffer);

		assertByte("First popped value should be the first pushed.", firstPopped, firstPushed);
		assertByte("Second popped value should be the second pushed.", secondPopped, secondPushed);
	}
	endTest();

	beginTest("Push/pop should in-/decrease size.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);
		assertByte("Fresh buffer should be empty.", circularBufferSize(&circularBuffer), 0);

		circularBufferPush(&circularBuffer, Direction_up);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPush(&circularBuffer, Direction_up);
		assertByte("Pushing should increase size.", circularBufferSize(&circularBuffer), 2);

		circularBufferPop(&circularBuffer);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 1);

		circularBufferPop(&circularBuffer);
		assertByte("Popping should decrease size.", circularBufferSize(&circularBuffer), 0);
	}
	endTest();

	beginTest("Push too many elements.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);

		for (int i = 0x00; i < 0xff; ++i)
		{
			bool success = circularBufferPush(&circularBuffer, Direction_up);
			assertTrue("Should be able to push exactly 0xff - 1 bytes.", success);
		}

		bool success = circularBufferPush(&circularBuffer, Direction_up);
		assertTrue("The buffer should be full now.", !success);
	}
	endTest();

	beginTest("Pop too many elements.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);

		circularBufferPush(&circularBuffer, Direction_up);
		circularBufferPop(&circularBuffer);
		assertByte("Should be back at zero size.", circularBufferSize(&circularBuffer), 0);
		circularBufferPop(&circularBuffer);
		assertByte("Popping too many should not decrease size.", circularBufferSize(&circularBuffer), 0);
	}
	endTest();

	beginTest("Push past the end, looping back.");
	{
		circularBufferInit(&circularBuffer, circularBufferValues);

		// Prep the buffer by pushing and popping to nearly capacity.
		for (int i = 0; i < 250; ++i)
		{
			circularBufferPush(&circularBuffer, Direction_up);
			circularBufferPop(&circularBuffer);
		}

		// A few more pushes will bring it over the edge and loop back at the beginning.
		for (int i = 0; i < 10; ++i)
		{
			Direction pushed = i % Direction_count;
			circularBufferPush(&circularBuffer, pushed);
			Direction popped = circularBufferPop(&circularBuffer);
			assertByte("Popped value should be same as pushed.", popped, pushed);
		}
	}
	endTest();
}
