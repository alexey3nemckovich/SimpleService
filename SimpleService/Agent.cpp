#include "stdafx.h"
#include "Agent.h"
#include "BackgroundWork.h"


AppInstance& AppInstance::Instance()
{
	return App::Instance();
}

App& App::Instance()
{
	static App instance;
	return instance;
}

App::App()
{

}

App::~App()
{

}

void App::OnStart()
{
	AppInstance::OnStart();

    BackgroundWork::Instance().Start();
}

void App::OnStop()
{
    BackgroundWork::Instance().Stop();

	AppInstance::OnStop();
}
