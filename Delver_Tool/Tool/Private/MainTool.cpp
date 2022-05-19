#include "..\Public\MainTool.h"

#include "GameInstance.h"
#include "Texture.h"
#include "VIBuffer_Rect.h"
#include "BackGround.h"

CMainTool::CMainTool()
	: m_pGameInstance(CGameInstance::Get_Instance()),
	m_pImgui_Manager(CImgui_Manager::Get_Instance())
{
	Safe_AddRef(m_pGameInstance);
	Safe_AddRef(m_pImgui_Manager);
}

HRESULT CMainTool::NativeConstruct()
{
	GRAPHICDESC		GraphicDesc;
	ZeroMemory(&GraphicDesc, sizeof(GRAPHICDESC));

	GraphicDesc.hWnd = g_hWnd;
	GraphicDesc.iWinCX = g_iWinSizeX;
	GraphicDesc.iWinCY = g_iWinSizeY;
	GraphicDesc.isWindowed = true;

	if (FAILED(m_pGameInstance->Initialize_Engine(LEVEL_END, GraphicDesc, &m_pGraphic_Device)))
		return E_FAIL;

	if (FAILED(Ready_RenderState()))
		return E_FAIL;

	if (FAILED(Ready_Prototype_Component_Static()))
		return E_FAIL;

	if (FAILED(m_pImgui_Manager->NativeConstruct(m_pGraphic_Device)))
		return E_FAIL;

	return S_OK;
}

void CMainTool::Tick(float fTimeDelta)
{
	if (nullptr == m_pGameInstance)
		return;

#ifdef _DEBUG
	m_fTimeAcc += fTimeDelta;
#endif // _DEBUG

	m_pGameInstance->Tick_Engine(fTimeDelta);

}

HRESULT CMainTool::Render()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;
	m_pGameInstance->Render_Begin();
	m_pImgui_Manager->Render_Begin();

	// ¿£Áø ·»´õ¸µ
	m_pGameInstance->Render_Engine();


	// Imgui ·»´õ¸µ
	ImGui::ShowDemoWindow();
	//Img_Test();
	FileTest();


#ifdef _DEBUG
	++m_iNumRender;

	_tchar	szFPS[MAX_PATH];
	if (m_fTimeAcc > 1.f)
	{
		wsprintf(szFPS, TEXT("FPS : %d \n"), m_iNumRender);
		SetWindowText(g_hWnd, szFPS);

		m_fTimeAcc = 0.f;
		m_iNumRender = 0;
	}
#endif

	m_pImgui_Manager->Render_End();
	m_pGameInstance->Render_End();

	return S_OK;
}

HRESULT CMainTool::Ready_RenderState()
{
	m_pGraphic_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//m_pGraphic_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//m_pGraphic_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pGraphic_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//m_pGraphic_Device->SetRenderState(D3DRS_ALPHAREF, 0);


	return S_OK;
}


HRESULT CMainTool::Ready_Prototype_Component_Static()
{
	if (nullptr == m_pGameInstance)
		return E_FAIL;

	/* Prototype_Component_VIBuffer_Rect */
	if (FAILED(m_pGameInstance->Add_ComponentPrototype(LEVEL_STATIC, TEXT("Prototype_Component_VIBuffer_Rect"),
		CVIBuffer_Rect::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* Prototype_Component_Texture_Logo */
	if (FAILED(m_pGameInstance->Add_ComponentPrototype(LEVEL_STATIC, L"Prototype_Component_Texture_Logo",
		CTexture::Create(m_pGraphic_Device, CTexture::TYPE_DEFAULT, L"../Bin/Resources/Monster.bmp", 1))))
		return E_FAIL;

	/* Prototype_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Add_ObjectPrototype(L"Prototype_GameObject_BackGround", CBackGround::Create(m_pGraphic_Device))))
		return E_FAIL;

	/* Clone_GameObject_BackGround */
	if (FAILED(m_pGameInstance->Clone_GameObject(LEVEL_STATIC, L"Layer_BackGround", L"Prototype_GameObject_BackGround")))
		return E_FAIL;

	return S_OK;
}

void CMainTool::FileTest()
{
	ImGui::Begin("File");
	// open Dialog Simple
	if (ImGui::Button("Open File Dialog"))
		ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".*", ".");

	// display
	if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
	{
		// action if OK
		if (ImGuiFileDialog::Instance()->IsOk())
		{
			std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
			std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
			// action
		}
		// close
		ImGuiFileDialog::Instance()->Close();
	}
	ImGui::End();

}


void CMainTool::Img_Test()
{
	int my_image_width = 0;
	int my_image_height = 0;
	LPDIRECT3DTEXTURE9 my_texture = NULL;
	bool ret = LoadTextureFromFile("../Bin/Resources/MyImage01.jpg", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
	ImGui::Begin("DirectX9 Texture Test");
	ImGui::Text("pointer = %p", my_texture);
	ImGui::Text("size = %d x %d", my_image_width, my_image_height);

	float x = 0.f;
	ImGui::DragFloat("X Pos", &x);
	ImGui::Image((void*)my_texture, ImVec2((float)my_image_width, (float)my_image_height));
	ImGui::End();
}

bool CMainTool::LoadTextureFromFile(const char * filename, LPDIRECT3DTEXTURE9 * out_texture, int * out_width, int * out_height)
{
	LPDIRECT3DTEXTURE9 texture;
	HRESULT hr = D3DXCreateTextureFromFileA(m_pGraphic_Device, filename, &texture);
	if (hr != S_OK)
		return false;

	// Retrieve description of the texture surface so we can access its size
	D3DSURFACE_DESC my_image_desc;
	texture->GetLevelDesc(0, &my_image_desc);
	*out_texture = texture;
	*out_width = (int)my_image_desc.Width;
	*out_height = (int)my_image_desc.Height;
	return true;
}

CMainTool * CMainTool::Create()
{
	CMainTool*		pInstance = new CMainTool();

	if (FAILED(pInstance->NativeConstruct()))
	{
		MSG_BOX("Failed to Created : CMainApp");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CMainTool::Free()
{
	__super::Free();

	Safe_Release(m_pGameInstance);

	Safe_Release(m_pGraphic_Device);
	
	Safe_Release(m_pImgui_Manager);

	CImgui_Manager::Destroy_Instance();

	CGameInstance::Release_Engine();
}
