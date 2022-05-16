#include "..\Public\Level_Manager.h"
#include "Level.h"

#include "Object_Manager.h"
#include "Component_Manager.h"

IMPLEMENT_SINGLETON(CLevel_Manager)

CLevel_Manager::CLevel_Manager()
{


}

HRESULT CLevel_Manager::Change_Level(_uint iLevelIndex, CLevel * pNextLevel)
{
	if (nullptr == pNextLevel)
		return E_FAIL;

	if (FAILED(Clear_LevelComponent(m_iLevelIndex)))
		return E_FAIL;

	Safe_Release(m_pCurrentLevel);

	m_pCurrentLevel = pNextLevel;	
	m_iLevelIndex = iLevelIndex;

	return S_OK;
}

HRESULT CLevel_Manager::Tick(_float fTimeDelta)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->Tick(fTimeDelta);

	return S_OK;
}

HRESULT CLevel_Manager::LateTick(_float fTimeDelta)
{
	if (nullptr == m_pCurrentLevel)
		return E_FAIL;

	m_pCurrentLevel->LateTick(fTimeDelta);

	return S_OK;
}

HRESULT CLevel_Manager::Clear_LevelComponent(_uint iLevelIndex)
{
	if (iLevelIndex == 0)
		return S_OK;

	if (FAILED(CObject_Manager::Get_Instance()->Clear(iLevelIndex)))
		return E_FAIL;

	if (FAILED(CComponent_Manager::Get_Instance()->Clear(iLevelIndex)))
		return E_FAIL;

	return S_OK;
}

void CLevel_Manager::Free()
{
	Safe_Release(m_pCurrentLevel);
}



