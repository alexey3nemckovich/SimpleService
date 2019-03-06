#pragma once
#include "Runnable.h"
#include <thread>
#include <memory>


class BackgroundExecutor abstract:
	public Runnable
{
public:
	typedef std::shared_ptr<BackgroundExecutor> Ptr;

protected:
	virtual void Run() = 0;

protected:
	virtual void OnStart() override;
	virtual void OnStop() override;

private:
	std::thread m_listeningThread;
};
