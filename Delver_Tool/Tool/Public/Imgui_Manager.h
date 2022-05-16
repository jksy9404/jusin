#pragma once

#include "Tool_Defines.h"
#include "Base.h"
#include "imgui.h"

BEGIN(Tool)

class CImgui_Manager final : public CBase
{
	DECLARE_SINGLETON(CImgui_Manager)
private:
	CImgui_Manager();
	virtual ~CImgui_Manager() = default;

public:
	void	Tick();

private:
	bool	showing = true;
	bool	fov = false;
	float	size = 2.f;

public:
	virtual void Free() override;
};

END