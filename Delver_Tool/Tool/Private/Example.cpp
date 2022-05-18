#include "..\Public\Example.h"
#include "Imgui_Manager.h"



CExample::CExample()
{
}


CExample::~CExample()
{
	

	Safe_Release(texture);

	Safe_Release(my_texture);
	
	Safe_Release(m_pGraphic_Device);
}

HRESULT CExample::NativeConstruct(LPDIRECT3DDEVICE9 pGraphic_Device)
{


	m_pGraphic_Device = pGraphic_Device;
	Safe_AddRef(m_pGraphic_Device);

	bool ret = LoadTextureFromFile("../Bin/Resources/MyImage01.jpg", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
	return S_OK;

}

void CExample::Render()
{

	if (GetAsyncKeyState(VK_DELETE) & 1)
		showing = !showing;

	if (showing)
	{
		//원그리기
		CreateSpapes();
		//이미지 띄우기
		 CreateImg();
		//이미지버튼 생성
	//	CreateImageButton();

	}
}

void CExample::CreateSpapes()
{
	ImGui::Begin("Draw Spapes");
	ImGui::Text("< Draw Circle >");
	ImGui::Checkbox("Circle fov", &Circlefov);
	ImGui::SliderFloat("Circle size", &Circlesize, 0, 500, "%.3f size");
	ImGui::Text("< Draw Rect >");
	ImGui::Checkbox("Rect fov", &Rectfov);
	ImGui::SliderFloat("Rect size", &Rectsize, 0, 500, "%.3f size");

	ImGui::End();

	if (Circlefov)
	{
		ImGui::Begin("Circle", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

		auto draw = ImGui::GetBackgroundDrawList();
		draw->AddCircle(ImVec2(g_iWinSizeX / 2, g_iWinSizeY / 2), Circlesize, IM_COL32(255, 0, 0, 255), 100, 1.0f);
		ImGui::End();
	}
	if (Rectfov)
	{
		ImGui::Begin("Rect", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

		auto draw = ImGui::GetBackgroundDrawList();
		draw->AddRect(ImVec2(g_iWinSizeX / 2 - Rectsize, g_iWinSizeY / 2 - Rectsize) , ImVec2(g_iWinSizeX / 2 + Rectsize, g_iWinSizeY / 2 + Rectsize), IM_COL32(255, 0, 0, 255));
		ImGui::End();
	}
}

void CExample::CreateImg()
{
	ImGui::Begin("Image");
	int my_image_width = 0;
	int my_image_height = 0;
	//LPDIRECT3DTEXTURE9 my_texture = NULL;
	bool ret = LoadTextureFromFile("../Bin/Resources/MyImage01.jpg", &my_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret);
	//ImGui::Text("pointer = %p", my_texture);
	ImGui::Text("size = %.2f x %.2f", my_image_width * 0.5f, my_image_height * 0.5f);

	float x = 0.f;
	//ImGui::DragFloat("X Pos", &x);
	ImGui::Image((void*)my_texture, ImVec2((float)my_image_width * 0.5f, (float)my_image_height * 0.5f));
	ImGui::End();
}

void CExample::CreateImageButton()
{
	
	ImGui::Begin("Image");

	ImGui::Text("< Create ImageButton >");

	if (ImGui::ImageButton((void*)my_texture, ImVec2((float)my_image_width * 0.5f, (float)my_image_height* 0.5f)))
		imageButtonClick_Count++;

	ImGui::Text("clickCount = %d", imageButtonClick_Count);

	ImGui::End();
}



bool CExample::LoadTextureFromFile(const char * filename, PDIRECT3DTEXTURE9 * out_texture, int * out_width, int * out_height)
{
	
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
