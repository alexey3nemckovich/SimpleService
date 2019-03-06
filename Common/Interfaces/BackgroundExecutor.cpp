#include <stdafx.h>
#include "BackgroundExecutor.h"
#include <Windows.h>


void BackgroundExecutor::OnStart()
{
	m_listeningThread = std::thread(&BackgroundExecutor::Run, this);
}

void BackgroundExecutor::OnStop()
{
	m_listeningThread.join();
}
