#include "StateController.h"

namespace fe
{

// =============================================================================
//	CONSTRUCTORS, COPY CONSTRUCTOR, DESTRUCTOR, ASSIGNMENT OPERATOR
// =============================================================================
StateController::StateController() :
	m_State(TInternalState::STOPPED),
	m_RunCallback(nullptr),
	m_PauseCallback(nullptr),
	m_UnpauseCallback(nullptr),
	m_StopCallback(nullptr)
{
}

StateController::~StateController()
{
}

// =============================================================================
//	REGULAR METHODS
// =============================================================================
bool StateController::run()
{
	if(m_State != TInternalState::STOPPED)
		return false;

	m_State = TInternalState::RUNNING;

	if(m_RunCallback != nullptr)
		m_RunCallback();

	return true;
}

bool StateController::pause()
{
	if(m_State != TInternalState::RUNNING)
		return false;

	m_State = TInternalState::PAUSED;

	if(m_PauseCallback != nullptr)
		m_PauseCallback();

	return true;
}

bool StateController::unpause()
{
	if(m_State != TInternalState::PAUSED)
		return false;

	m_State = TInternalState::RUNNING;

	if(m_UnpauseCallback != nullptr)
		m_UnpauseCallback();

	return true;
}

bool StateController::stop()
{
	if(m_State == TInternalState::STOPPED)
		return false;

	m_State = TInternalState::STOPPED;

	if(m_StopCallback != nullptr)
		m_StopCallback();

	return true;
}

// =============================================================================
//	GETTERS & SETTERS
// =============================================================================
void StateController::setRunCallback(const Callback& callback)     { m_RunCallback = callback;     }
void StateController::setPauseCallback(const Callback& callback)   { m_PauseCallback = callback;   }
void StateController::setUnpauseCallback(const Callback& callback) { m_UnpauseCallback = callback; }
void StateController::setStopCallback(const Callback& callback)    { m_StopCallback = callback;    }

// =============================================================================
//	QUESTION METHODS
// =============================================================================
bool StateController::isRunning() const { return m_State == TInternalState::RUNNING; }
bool StateController::isPaused() const  { return m_State == TInternalState::PAUSED;  }
bool StateController::isStopped() const { return m_State == TInternalState::STOPPED; }

}
