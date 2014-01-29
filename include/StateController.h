#ifndef __STATE_CONTROLLER_H__
#define __STATE_CONTROLLER_H__

#include <functional>

namespace fe
{

enum class TInternalState
{
	RUNNING,
	PAUSED,
	STOPPED
};

class StateController
{
private:
	typedef std::function<void()> Callback;

	TInternalState m_State;

	Callback m_RunCallback;
	Callback m_PauseCallback;
	Callback m_UnpauseCallback;
	Callback m_StopCallback;

public:
	StateController();
	StateController(const StateController& toCopy);
	StateController& operator=(const StateController& toCopy);
	~StateController();

	bool run();
	bool pause();
	bool unpause();
	bool stop();

	void setRunCallback(const Callback& callback);
	void setPauseCallback(const Callback& callback);
	void setUnpauseCallback(const Callback& callback);
	void setStopCallback(const Callback& callback);

	bool isRunning() const;
	bool isPaused() const;
	bool isStopped() const;
};

}

#endif
