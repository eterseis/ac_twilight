#include "menu.h"

void Menu::Tabs(std::unordered_map<int, std::string> btns)
{
	for (const auto& i : btns)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.0f);

		if (selected_tab == i.first)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_ButtonHovered));
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyleColorVec4(ImGuiCol_Button));
		}

		ImGui::SameLine();
		if (ImGui::Button(i.second.c_str(), btn_size))
		{
			selected_tab = i.first;
		}

		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor();
	}
}

void Menu::Render(int width, int height)
{
	std::unordered_map<int, std::string> btns
	{
		{0, "Visuals"},
		{1, "Aim"},
		{2, "Misc"},
	};

	ImGui::SetNextWindowSize(ImVec2(width * 0.4f, height * 0.4f));
	ImGui::Begin("ac_twilight", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

	btn_size = ImVec2(ImGui::GetWindowWidth() / std::ssize(btns) - 2.8f, 30.0f);
	Menu::Tabs(btns);

	ImGui::Separator();

	if (selected_tab == 0) // Visuals
	{
		ImGuiColorEditFlags base_flags{ ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha };

		ImGui::SeparatorText("ESP");
		ImGui::Checkbox("Enabled##1", &Settings::visuals_enabled);
		ImGui::Checkbox("Ignore Teammates", &Settings::visuals_ignore_teammates);
		ImGui::Checkbox("Outlined", &Settings::visuals_outlined);

		ImGui::SeparatorText("Snaplines");
		ImGui::Checkbox("Enabled##2", &Settings::visuals_snaplines);
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 4.0f);
		ImGui::ColorEdit4("Snaplines Color", reinterpret_cast<float*>(&Settings::visuals_snaplines_color), base_flags);

		ImGui::SeparatorText("Health Bar");
		ImGui::Checkbox("Enabled", &Settings::visuals_health_bar);
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 4.0f);
		ImGui::ColorEdit4("Health Bar Color", reinterpret_cast<float*>(&Settings::visuals_health_bar_color), base_flags);

		ImGui::SeparatorText("Bounding Box");
		ImGui::Checkbox("Enabled##4", &Settings::visuals_bounding_box);
		ImGui::SameLine();
		ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 4.0f);
		ImGui::ColorEdit4("Bounding Box Color", reinterpret_cast<float*>(&Settings::visuals_bounding_box_color), base_flags);

		ImGui::Checkbox("Filled", &Settings::visuals_filled_bounding_box);
	}

	if (selected_tab == 1) // Aim
	{
		ImGui::SeparatorText("Aimbot");
		ImGui::Checkbox("Enabled##8", &Settings::aim_enabled);
		ImGui::Checkbox("Ignore Teammates", &Settings::aim_ignore_teammates);
	}

	if (selected_tab == 2) // Misc
	{
		ImGui::SeparatorText("Unlimited Health");
		ImGui::Checkbox("Enabled##5", &Settings::misc_unlimited_health);

		ImGui::SeparatorText("Unlimited Ammo");
		ImGui::Checkbox("Enabled##6", &Settings::misc_unlimited_ammo);

		ImGui::SeparatorText("Rapidfire");
		ImGui::Checkbox("Enabled##7", &Settings::misc_rapidfire);
		ImGui::SliderInt("Delay", &Settings::misc_rapidfire_delay, 0, 40);
	}

	ImGui::End();
}