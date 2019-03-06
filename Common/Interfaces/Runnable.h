#pragma once


class Runnable abstract
{
public:
	enum class State
	{
		Starting,
		Running,
		Stopping,
		Stopped
	};

public:
	Runnable();
	virtual ~Runnable();

public:
	void Start();
	void Stop();

public:
	bool IsRunning() const;

public:
	State GetState() const;

protected:
	virtual void OnStart() = 0;
	virtual void OnStop() = 0;

private:
	void UpdateState(State state);

private:
	State m_state;
};
