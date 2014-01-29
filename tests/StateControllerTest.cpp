#include "StateControllerTest.h"

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
StateControllerTest::StateControllerTest() :
	m_StateController(nullptr)
{
}

StateControllerTest::~StateControllerTest()
{
}

// =============================================================================
//	TEST STARTUP / TEARDOWN
// =============================================================================
void StateControllerTest::setUp()
{
	m_StateController = new StateController();
}

void StateControllerTest::tearDown()
{
	if(m_StateController != nullptr)
		delete m_StateController;
}

// =============================================================================
//	TEST CASES
// =============================================================================
void StateControllerTest::testDefaultState()
{
	CPPUNIT_ASSERT(m_StateController->isStopped());
}

// -------------------- REGULAR METHODS -------------------------

void StateControllerTest::testRunReturnsTrue()
{
	CPPUNIT_ASSERT(m_StateController->run());
	m_StateController->stop();
	CPPUNIT_ASSERT(m_StateController->run());
}

void StateControllerTest::testRunReturnsFalse()
{
	m_StateController->run();
	CPPUNIT_ASSERT( ! m_StateController->run());

	m_StateController->pause();
	CPPUNIT_ASSERT( ! m_StateController->run());

	m_StateController->unpause();
	CPPUNIT_ASSERT( ! m_StateController->run());
}

void StateControllerTest::testPauseReturnsTrue()
{
	m_StateController->run();
	CPPUNIT_ASSERT(m_StateController->pause());

	m_StateController->unpause();
	CPPUNIT_ASSERT(m_StateController->pause());
}

void StateControllerTest::testPauseReturnsFalse()
{
	CPPUNIT_ASSERT( ! m_StateController->pause());

	m_StateController->run();
	m_StateController->pause();
	CPPUNIT_ASSERT( ! m_StateController->pause());

	m_StateController->unpause();
	m_StateController->stop();
	CPPUNIT_ASSERT( ! m_StateController->pause());
}

void StateControllerTest::testUnpauseReturnsTrue()
{
	m_StateController->run();
	m_StateController->pause();
	CPPUNIT_ASSERT(m_StateController->unpause());
}

void StateControllerTest::testUnpauseReturnsFalse()
{
	CPPUNIT_ASSERT( ! m_StateController->unpause());

	m_StateController->run();
	CPPUNIT_ASSERT( ! m_StateController->unpause());

	m_StateController->pause();
	m_StateController->unpause();
	CPPUNIT_ASSERT( ! m_StateController->unpause());

	m_StateController->stop();
	CPPUNIT_ASSERT( ! m_StateController->unpause());
}

void StateControllerTest::testStopReturnsTrue()
{
	m_StateController->run();
	CPPUNIT_ASSERT(m_StateController->stop());

	m_StateController->run();
	m_StateController->pause();
	CPPUNIT_ASSERT(m_StateController->stop());
}

void StateControllerTest::testStopReturnsFalse()
{
	CPPUNIT_ASSERT( ! m_StateController->stop());
}

// ----------------------------- GETTERS & SETTERS -----------------------------

void StateControllerTest::testSetRunCallback()
{
	bool called = false;
	m_StateController->setRunCallback([&] () { called = true; });

	m_StateController->run();

	if(called)
		return;

	CPPUNIT_FAIL("Code can't reach that line");
}

void StateControllerTest::testSetPauseCallback()
{
	bool called = false;
	m_StateController->setPauseCallback([&] () { called = true; });

	m_StateController->run();
	m_StateController->pause();

	if(called)
		return;

	CPPUNIT_FAIL("Code can't reach that line");
}

void StateControllerTest::testSetUnpauseCallback()
{
	bool called = false;
	m_StateController->setUnpauseCallback([&] () { called = true; });

	m_StateController->run();
	m_StateController->pause();
	m_StateController->unpause();

	if(called)
		return;

	CPPUNIT_FAIL("Code can't reach that line");
}

void StateControllerTest::testSetStopCallback()
{
	bool called = false;
	m_StateController->setStopCallback([&] () { called = true; });

	m_StateController->run();
	m_StateController->stop();

	if(called)
		return;

	CPPUNIT_FAIL("Code can't reach that line");
}

// ---------------------------- QUESTION METHODS TESTS -------------------------

void StateControllerTest::testIsRunningReturnsTrue()
{
	m_StateController->run();
	CPPUNIT_ASSERT(m_StateController->isRunning());

	m_StateController->pause();
	m_StateController->unpause();
	CPPUNIT_ASSERT(m_StateController->isRunning());
}

void StateControllerTest::testIsRunningReturnsFalse()
{
	CPPUNIT_ASSERT( ! m_StateController->isRunning());

	m_StateController->run();
	m_StateController->pause();
	CPPUNIT_ASSERT( ! m_StateController->isRunning());

	m_StateController->stop();
	CPPUNIT_ASSERT( ! m_StateController->isRunning());
}

void StateControllerTest::testIsPausedReturnsTrue()
{
	m_StateController->run();
	m_StateController->pause();
	CPPUNIT_ASSERT(m_StateController->isPaused());
}

void StateControllerTest::testIsPausedReturnsFalse()
{
	CPPUNIT_ASSERT( ! m_StateController->isPaused());

	m_StateController->run();
	CPPUNIT_ASSERT( ! m_StateController->isPaused());

	m_StateController->pause();
	m_StateController->unpause();
	CPPUNIT_ASSERT( ! m_StateController->isPaused());
}

void StateControllerTest::testIsStoppedReturnsTrue()
{
	CPPUNIT_ASSERT(m_StateController->isStopped());

	m_StateController->run();
	m_StateController->stop();
	CPPUNIT_ASSERT(m_StateController->isStopped());

	m_StateController->run();
	m_StateController->pause();
	m_StateController->stop();
	CPPUNIT_ASSERT(m_StateController->isStopped());
}

void StateControllerTest::testIsStoppedReturnsFalse()
{
	m_StateController->run();
	CPPUNIT_ASSERT( ! m_StateController->isStopped());

	m_StateController->pause();
	CPPUNIT_ASSERT( ! m_StateController->isStopped());
}

}
