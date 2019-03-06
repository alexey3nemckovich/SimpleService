#include <stdafx.h>
#include "Runnable.h"


Runnable::Runnable():
	m_state(State::Stopped)
{

}

Runnable::~Runnable()
{

}

void Runnable::Start()
{
	UpdateState(State::Starting);

	OnStart();

	UpdateState(State::Running);
}

void Runnable::Stop()
{
	UpdateState(State::Stopping);

	OnStop();

	UpdateState(State::Stopped);
}

bool Runnable::IsRunning() const
{
	return 
        State::Running == m_state ||
        State::Starting == m_state;
}

Runnable::State Runnable::GetState() const
{
	return m_state;
}

void Runnable::UpdateState(State state)
{
	m_state = state;
}
