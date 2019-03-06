#pragma once
#include "Runnable.h"


class AppInstance abstract:
	public Runnable
{
public:
	static AppInstance& Instance();

	AppInstance() = default;
	virtual ~AppInstance() = default;

protected:
	virtual void OnStart() override;
	virtual void OnStop() override;
};
