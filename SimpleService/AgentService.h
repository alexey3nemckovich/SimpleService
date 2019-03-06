#pragma once
#include "..\Common\Interfaces\BaseService.h"


class AgentService sealed:
	public BaseService
{
public:
	AgentService();

protected:
	virtual void HandleControl(
		DWORD    dwControl,
		DWORD    dwEventType,
		LPVOID   lpEventData,
		LPVOID   lpContext
	) override;

	virtual std::string GetServiceName() override;
	virtual std::string GetServiceDisplayName() override;
};
