#pragma once
#include "..\Common\Interfaces\BackgroundExecutor.h"
#include "..\Common\Interfaces\Singleton.h"


class BackgroundWork:
    public BackgroundExecutor,
    public Singletone<BackgroundWork>
{
protected:
    virtual void Run() override;
};
