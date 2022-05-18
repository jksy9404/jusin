#include "stdafx.h"
#include "..\Public\Loader.h"
#include "GameInstance.h"

#include "BackGround.h"
#include "Texture.h"

CLoader::CLoader(LPDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}


/*
typedef unsigned (__stdcall  *_beginthreadex_proc_type)(void*);
*/

unsigned int APIENTRY ThreadEntryFunc(void* pArg)
{

	CLoader*		pLoader = (CLoader*)pArg;

	EnterCriticalSection(pLoader->Get_CriticalSection());

	/* �ڿ��ε��Ҳ���. */
	switch (pLoader->Get_NextLevelID())
	{
	case LEVEL_LOGO:
		pLoader->Loading_ForLogoLevel();
		break;
	case LEVEL_GAMEPLAY:
		pLoader->Loading_ForGamePlayLevel();
		break;
	}	

	LeaveCriticalSection(pLoader->Get_CriticalSection());

	return 0;
}




HRESULT CLoader::NativeConstruct(LEVEL eNextLevel)
{
	m_eNextLevel = eNextLevel;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadEntryFunc, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoader::Loading_ForLogoLevel()
{
	CGameInstance*		pGameInstance = CGameInstance::Get_Instance();
	if (nullptr == pGameInstance)
		return E_FAIL;

	Safe_AddRef(pGameInstance);

	wsprintf(m_szLoading, TEXT("�ΰ�� �ؽ��ĸ� �ε� ���Դϴ�. \n"));

	if (FAILED(CGameInstance::Get_Instance()->Add_ComponentPrototype(LEVEL_LOGO, L"Prototype_Component_Texture_Logo", 
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, L"../Bin/Resources/Monster.bmp", 1))))
		return E_FAIL;


	wsprintf(m_szLoading, TEXT("�ΰ�� �𵨸� �ε� ���Դϴ�. \n"));
	
	wsprintf(m_szLoading, TEXT("�ΰ�� ��ü���� ���� ���� ���Դϴ�. \n"));

	/* For.Prototype_GameObject_BackGround*/
	if (FAILED(pGameInstance->Add_ObjectPrototype(TEXT("Prototype_GameObject_BackGround"),
		CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;	

	wsprintf(m_szLoading, TEXT("�ε��� �Ϸ�Ǿ����ϴ�. \n"));
	
	Safe_Release(pGameInstance);

	m_isFinished = true;
	
	return S_OK;
}

HRESULT CLoader::Loading_ForGamePlayLevel()
{

	wsprintf(m_szLoading, TEXT("�����÷��̿� �ؽ��ĸ� �ε� ���Դϴ�. \n"));

	wsprintf(m_szLoading, TEXT("�����÷��̿� �𵨸� �ε� ���Դϴ�. \n"));

	wsprintf(m_szLoading, TEXT("�����÷��̿� ��ü���� ���� ���Դϴ�. \n"));

	wsprintf(m_szLoading, TEXT("�����÷��̿� �Ϸ�Ǿ����ϴ�. \n"));

	m_isFinished = true;

	return S_OK;
}

CLoader * CLoader::Create(LPDIRECT3DDEVICE9 pGraphic_Device, LEVEL eNextLevel)
{
	CLoader*		pInstance = new CLoader(pGraphic_Device);

	if (FAILED(pInstance->NativeConstruct(eNextLevel)))
	{
		MSG_BOX("Failed to Created : CLoader");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoader::Free()
{
	Safe_Release(m_pGraphic_Device);

	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_hThread);
}

