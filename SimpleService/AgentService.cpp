#include "stdafx.h"
#include "Agent.h"
#include "AgentService.h"

std::unique_ptr<BaseService> pService = std::make_unique<AgentService>(AgentService());


AgentService::AgentService()
{

}

void AgentService::HandleControl(
	DWORD    dwControl,
	DWORD    dwEventType,
	LPVOID   lpEventData,
	LPVOID   lpContext
)
{
	switch (dwControl)
	{
		//todo
	}
}

std::string AgentService::GetServiceName()
{
	return "SimpleService";
}

std::string AgentService::GetServiceDisplayName()
{
	return "ES Simple service!!!";
}
