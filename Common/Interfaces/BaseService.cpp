#include <stdafx.h>
#include <memory>
#include "BaseService.h"
#include "AppInstance.h"
#include <functional>


extern std::unique_ptr<BaseService> pService;

BaseService::BaseService()
{

}

void BaseService::StartDispatcher()
{
	SERVICE_TABLE_ENTRYA serviceTable[] = {
		{
			(LPSTR)GetServiceName().c_str(),
			BaseService::Run
		},
		{
			NULL,
			NULL
		}
	};

	StartServiceCtrlDispatcherA(serviceTable);
}

void BaseService::Start()
{
	SC_HANDLE hServiceControlManager = OpenSCManager(0, 0, SC_MANAGER_CONNECT);

	if (hServiceControlManager)
	{
		SC_HANDLE hService = OpenServiceA(
			hServiceControlManager,
			GetServiceName().c_str(),
			SERVICE_START
		);

		if (hService)
		{
			StartService(hService, 0, NULL);
			CloseServiceHandle(hService);
		}

		CloseServiceHandle(hServiceControlManager);
	}
}

void BaseService::Stop()
{
	SC_HANDLE hServiceControlManager = OpenSCManager(0, 0, SC_MANAGER_CONNECT);

	if (hServiceControlManager)
	{
		SC_HANDLE hService = OpenServiceA(
			hServiceControlManager,
			GetServiceName().c_str(),
			SERVICE_STOP
		);

		if (hService)
		{
			ControlService(hService, SERVICE_CONTROL_STOP, &m_serviceStatus);
			CloseServiceHandle(hService);
		}

		CloseServiceHandle(hServiceControlManager);
	}
}

void BaseService::Install()
{
	SC_HANDLE hServiceControlManager = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);

	if (hServiceControlManager)
	{
		char path[_MAX_PATH + 1];
		if (GetModuleFileNameA(0, path, sizeof(path) / sizeof(path[0])) > 0)
		{
			SC_HANDLE hService = CreateServiceA(
				hServiceControlManager,
				GetServiceName().c_str(),
				GetServiceDisplayName().c_str(),
				SERVICE_ALL_ACCESS,
				SERVICE_WIN32_OWN_PROCESS,
				SERVICE_AUTO_START,
				SERVICE_ERROR_NORMAL,
				path,
                "Base",
                NULL, 
                NULL, 
                NULL,
                NULL
			);

			if (hService)
			{
				CloseServiceHandle(hService);
			}
            else
            {
                std::cout << "Failed to CreateServiceA(): " << GetLastError();
            }
		}
        else
        {
            std::cout << "Failed to GetModuleFileNameA(): " << GetLastError();
        }

		CloseServiceHandle(hServiceControlManager);
	}
    else
    {
        std::cout << "Failed to open SC manager: " << GetLastError();
    }
}

void BaseService::Uninstall()
{
	SC_HANDLE hServiceControlManager = OpenSCManager(0, 0, SC_MANAGER_CONNECT);

	if (hServiceControlManager)
	{
		SC_HANDLE hService = OpenServiceA(
			hServiceControlManager,
			GetServiceName().c_str(),
			SERVICE_QUERY_STATUS | DELETE
		);

		if (hService)
		{
			SERVICE_STATUS serviceStatus;
			if (QueryServiceStatus(hService, &serviceStatus))
			{
				if (serviceStatus.dwCurrentState == SERVICE_STOPPED)
				{
					DeleteService(hService);
				}
			}

			CloseServiceHandle(hService);
		}

		CloseServiceHandle(hServiceControlManager);
	}
}

void WINAPI BaseService::Run(DWORD /*argc*/, LPSTR lpServiceArgVectors[])
{
	pService->m_hServiceStatus = 
		RegisterServiceCtrlHandlerExA(pService->GetServiceName().c_str(), ControlHandler, NULL);

	if (pService->m_hServiceStatus)
	{
		pService->StartActions();

		WaitForSingleObject(pService->m_hServiceStoppedEvent, INFINITE);

		pService->StopActions();
	}
}

DWORD WINAPI BaseService::ControlHandler(
	DWORD    dwControl,
	DWORD    dwEventType,
	LPVOID   lpEventData,
	LPVOID   lpContext
)
{
	switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:
		{
			pService->UpdateStatus(SERVICE_STOP_PENDING);

			pService->OnStop();

			SetEvent(pService->m_hServiceStoppedEvent);
		}
		break;
	default:
		{
			pService->HandleControl(dwControl, dwEventType, lpEventData, lpContext);
		}
		break;
	}

	pService->UpdateStatus();
	return NO_ERROR;
}

void BaseService::OnStart()
{
	AppInstance::Instance().Start();
}

void BaseService::OnStop()
{
	AppInstance::Instance().Stop();
}

void BaseService::StartActions()
{
	InitStatus();
	UpdateStatus(SERVICE_START_PENDING);
	m_hServiceStoppedEvent = CreateEvent(0, FALSE, FALSE, 0);

	OnStart();

	UpdateStatus(SERVICE_RUNNING, SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN);
}

void BaseService::StopActions()
{
	CloseHandle(m_hServiceStoppedEvent);

	UpdateStatus(SERVICE_STOPPED, 0);
}

void BaseService::InitStatus()
{
	m_serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS;
	m_serviceStatus.dwControlsAccepted = 0;
	m_serviceStatus.dwWin32ExitCode = NO_ERROR;
	m_serviceStatus.dwServiceSpecificExitCode = NO_ERROR;
	m_serviceStatus.dwCheckPoint = 0;
	m_serviceStatus.dwWaitHint = 0;
}

void BaseService::UpdateStatus(DWORD dwState/* = NULL*/, DWORD dwControlsAccepted/* = NULL*/)
{
	if (dwState)
	{
		m_serviceStatus.dwCurrentState = dwState;
	}

	if (dwControlsAccepted)
	{
		m_serviceStatus.dwControlsAccepted = dwControlsAccepted;
	}

	SetServiceStatus(m_hServiceStatus, &m_serviceStatus);
}
