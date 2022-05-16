#pragma once

#include "Base.h"

/* ���� ���ӳ��� �����ִ� ������ �����Ѵ�. */
/* ������ ��ü �۾��� �����Ѵ�. (���������� ��ü���� �����Ѵ�.) */

BEGIN(Engine)

class CLevel_Manager final : public CBase
{
	DECLARE_SINGLETON(CLevel_Manager)
private:
	CLevel_Manager();
	virtual ~CLevel_Manager() = default;

public:
	HRESULT Change_Level(_uint iLevelIndex, class CLevel* pNextLevel);
	HRESULT Tick(_float fTimeDelta);
	HRESULT LateTick(_float fTimeDelta);

	HRESULT	Clear_LevelComponent(_uint iLevelIndex);

private:
	_uint					m_iLevelIndex = 0;
	class CLevel*			m_pCurrentLevel = nullptr;

public:
	virtual void Free() override;
};

END