
#include "../Public/Imgui_Manager.h"

IMPLEMENT_SINGLETON(CImgui_Manager)

CImgui_Manager::CImgui_Manager()
{
}

void CImgui_Manager::Tick()
{
	if (GetAsyncKeyState(VK_DELETE) & 1)
		showing = !showing;

	if (showing)
	{
		ImGui::Begin("test");
		ImGui::Checkbox("Circle fov", &fov);
		ImGui::SliderFloat("Circle size", &size, 0, 5, "%.3f size");

		ImGuiStyle* style2 = &ImGui::GetStyle();
		style2->WindowMinSize = ImVec2(100, 430);
		//style->WindowMax = ImVec2(100, 430);
		style2->Colors[ImGuiCol_TitleBg] = ImColor(255, 51, 53, 255);
		style2->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 81, 93, 255);
		style2->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);


		//camPosition = D3DXVECTOR3(size, 4.5f, -3.5f);
		ImGui::End();
		////
		ImGui::Begin("test2");
		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowMinSize = ImVec2(100, 430);
		//style->WindowMax = ImVec2(100, 430);
		style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
		style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);
		ImGui::End();
	}
}

void CImgui_Manager::Free()
{
	__super::Free();
}
