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

	//bool ret = LoadTextureFromFile("../Bin/Resources/MyImage01.jpg", &my_texture, &my_image_width, &my_image_height);
	//IM_ASSERT(ret);
	//return S_OK;

	bool ret = LoadTextureFromFile("../Bin/Resources/Monster.bmp", &my_texture, &my_image_width, &my_image_height);
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
		CreateImageButton();
		//마우스 위치 얻기
		GetMousePos();
		// File Dialog띄우기
		OpenFileDialog();
	}
}

void CExample::CreateSpapes()
{
	ImGui::Begin("Draw Spapes");
	
	ImVec2 mainViewCenterPos = ImGui::GetMainViewport()->GetCenter();
	
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
		draw->AddCircle(ImVec2(ImGui::GetMainViewport()->GetCenter().x , ImGui::GetMainViewport()->GetCenter().y ), Circlesize, IM_COL32(255, 0, 0, 255), 100, 1.0f);
		ImGui::End();
	}
	if (Rectfov)
	{
		ImGui::Begin("Rect", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar);

		auto draw = ImGui::GetBackgroundDrawList();
		draw->AddRect(ImVec2(mainViewCenterPos.x - Rectsize, mainViewCenterPos.y - Rectsize) , ImVec2(mainViewCenterPos.x + Rectsize, mainViewCenterPos.y + Rectsize), IM_COL32(255, 0, 0, 255));
		ImGui::End();
	}
}

void CExample::CreateImg()
{
	ImGui::Begin("Image");
	ImGui::Text("< Show Image >");
	ImGui::Text("size = %.2f x %.2f", my_image_width * 0.5f, my_image_height * 0.5f);

	float x = 0.f;
	//ImGui::DragFloat("X Pos", &x);
	ImGui::Image((void*)my_texture, ImVec2(32, 32), ImVec2(0, 0), ImVec2(0.0625f, 0.125f));
	ImGui::End();
}

void CExample::CreateImageButton()
{
	ImGui::Begin("Image");

	ImGui::Text("< Create ImageButton >");

	if (ImGui::ImageButton((void*)my_texture, ImVec2(32,32), ImVec2(0.0625f *(imageButtonClick_Count - 1)  ,0), ImVec2(0.0625f *imageButtonClick_Count, 0.125f)))
		imageButtonClick_Count++;

	ImGui::Text("ClickCount = %d", imageButtonClick_Count);

	ImGui::End();
}

void CExample::GetMousePos()
{
	ImGui::Begin("Get MousePos");

	ImVec2  screenMousePos = ImGui::GetMousePosOnOpeningCurrentPopup();
	ImVec2 mainViewPos = ImGui::GetMainViewport()->Pos;
	float getDistance_x = fabs(screenMousePos.x - mainViewPos.x);
	float getDistance_y = fabs(screenMousePos.y - mainViewPos.y);

	ImGui::Text("mainViewPos_x : %1.f, mainViewPos_y : %1.f", mainViewPos.x, mainViewPos.y);
	ImGui::Text("screenMousePos_x : %1.f, screenMousePos_y : %1.f", screenMousePos.x, screenMousePos.y);

	ImGui::Text("getDistance_x : %1.f, getDistance_y : %1.f", getDistance_x, getDistance_y);

	ImGui::Text("MainViewMousePos_x : %1.f", screenMousePos.x - mainViewPos.x);
	ImGui::Text("MainViewMousePos_y : %1.f", screenMousePos.y - mainViewPos.y);

	ImGui::End();
}

void CExample::OpenFileDialog()
{
	ImGui::Begin("OPen File Dialog");

	if (ImGui::Button("OPen File Dialog"))
	{
		OPENFILENAME ofn;
		::memset(&ofn, 0, sizeof(ofn));
		
		m_fileName[0] = 0;
		ofn.lStructSize = sizeof(ofn);
		ofn.nFilterIndex = 2;
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrFile = m_fileName;
		ofn.Flags = OFN_FILEMUSTEXIST;
		if (::GetOpenFileName(&ofn) != FALSE)
			WideCharToMultiByte(CP_ACP, 0, m_fileName, len, ctemp, len, NULL, NULL);//tchar->char
	}
	if (ctemp == nullptr)
	{
		ImGui::End();
		return;
	}
	ImGui::Text(ctemp);

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
