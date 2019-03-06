#pragma once
#include <string>
#include <Windows.h>


class BaseService
{
public:
	BaseService();

public:
	void StartDispatcher();

	void Start();
	void Stop();

	void Install();
	void Uninstall();

protected:
	//SERVICE_CONTROL_STOP event doesn't come here
	//To handle SERVICE_CONTROL_STOP override AppInstance::OnStop()
	virtual void HandleControl(
		DWORD    dwControl,
		DWORD    dwEventType,
		LPVOID   lpEventData,
		LPVOID   lpContext
	) = 0;

	virtual std::string GetServiceName() = 0;
	virtual std::string GetServiceDisplayName() = 0;

protected:
	void UpdateStatus(DWORD dwState = NULL, DWORD dwControlsAccepted = NULL);

private:
	static void WINAPI Run(DWORD /*argc*/, LPSTR lpServiceArgVectors[]);

	static DWORD WINAPI ControlHandler(
		DWORD    dwControl,
		DWORD    dwEventType,
		LPVOID   lpEventData,
		LPVOID   lpContext
	);

private:
	void OnStart();
	void OnStop();

private:
	void StartActions();
	void StopActions();

private:
	void InitStatus();

private:
	SERVICE_STATUS			m_serviceStatus;
	SERVICE_STATUS_HANDLE	m_hServiceStatus;

	HANDLE					m_hServiceStoppedEvent;
};
