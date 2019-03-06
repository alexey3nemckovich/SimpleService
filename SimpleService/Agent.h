#pragma once
#include <vector>
#include "..\Common\Interfaces\AppInstance.h"


class App sealed:
	public AppInstance
{
public:
	static App& Instance();

	App();
	~App();

protected:
	virtual void OnStart() override;
	virtual void OnStop() override;
};
