#include "stdafx.h"
#include "..\Common\Interfaces\BaseService.h"

extern std::unique_ptr<BaseService> pService;


int _tmain(int argc, TCHAR* argv[])
{
	if (argc > 1)
	{
		if (lstrcmpi(argv[1], TEXT("install")) == 0)
		{
			pService->Install();
		}

		if (lstrcmpi(argv[1], TEXT("uninstall")) == 0)
		{
			pService->Uninstall();
		}

		if (lstrcmpi(argv[1], TEXT("start")) == 0)
		{
			pService->Start();
		}

		if (lstrcmpi(argv[1], TEXT("stop")) == 0)
		{
			pService->Stop();
		}
	}
	else
	{
		pService->StartDispatcher();
	}

	return 0;
}
