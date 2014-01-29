#ifndef __STATE_CONTROLLER_TEST_H__
#define __STATE_CONTROLLER_TEST_H__

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "StateController.h"

using namespace CppUnit;

namespace fe
{

class StateControllerTest : public TestFixture
{
	CPPUNIT_TEST_SUITE(StateControllerTest);
	
	CPPUNIT_TEST(testDefaultState);

	CPPUNIT_TEST(testRunReturnsTrue);
	CPPUNIT_TEST(testRunReturnsFalse);
	CPPUNIT_TEST(testPauseReturnsTrue);
	CPPUNIT_TEST(testPauseReturnsFalse);
	CPPUNIT_TEST(testUnpauseReturnsTrue);
	CPPUNIT_TEST(testUnpauseReturnsFalse);
	CPPUNIT_TEST(testStopReturnsTrue);
	CPPUNIT_TEST(testStopReturnsFalse);

	CPPUNIT_TEST(testSetRunCallback);
	CPPUNIT_TEST(testSetPauseCallback);
	CPPUNIT_TEST(testSetUnpauseCallback);
	CPPUNIT_TEST(testSetStopCallback);

	CPPUNIT_TEST(testIsRunningReturnsTrue);
	CPPUNIT_TEST(testIsRunningReturnsFalse);
	CPPUNIT_TEST(testIsPausedReturnsTrue);
	CPPUNIT_TEST(testIsPausedReturnsFalse);
	CPPUNIT_TEST(testIsStoppedReturnsTrue);
	CPPUNIT_TEST(testIsStoppedReturnsFalse);

	CPPUNIT_TEST_SUITE_END();

private:
	StateController* m_StateController;

public:
	StateControllerTest();
	StateControllerTest(const StateControllerTest& toCopy);
	StateControllerTest& operator=(const StateControllerTest& toCopy);
	~StateControllerTest();

	virtual void setUp();
	virtual void tearDown();

	void testDefaultState();
	
	// Test cases for run() pause() unpause() stop()
	void testRunReturnsTrue();
	void testRunReturnsFalse();
	void testPauseReturnsTrue();
	void testPauseReturnsFalse();
	void testUnpauseReturnsTrue();
	void testUnpauseReturnsFalse();
	void testStopReturnsTrue();
	void testStopReturnsFalse();

	// Test cases for setters
	void testSetRunCallback();
	void testSetPauseCallback();
	void testSetUnpauseCallback();
	void testSetStopCallback();

	// Test cases for isRunning() isPaused() isStopped()
	void testIsRunningReturnsTrue();
	void testIsRunningReturnsFalse();
	void testIsPausedReturnsTrue();
	void testIsPausedReturnsFalse();
	void testIsStoppedReturnsTrue();
	void testIsStoppedReturnsFalse();
};

}

#endif
