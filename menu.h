#pragma once

#include <Windows.h>
#include <unordered_map>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "settings.h"

//inline bool visuals_enabled{};
//inline bool visuals_ignore_teammates{};
//inline bool visuals_outlined{};
//
//inline bool visuals_bounding_box{};
//inline ImVec4 visuals_bounding_box_color{ 1.0f, 0.0f, 0.0f, 1.0f };
//
//inline bool visuals_filled_bounding_box{};
//
//inline bool visuals_snaplines{};
//inline ImVec4 visuals_snaplines_color{ 1.0f, 0.0f, 0.0f, 1.0f };
//
//inline bool visuals_health_bar{};
//inline ImVec4 visuals_health_bar_color{ 0.0f, 1.0f, 0.0f, 1.0f };
//
//inline bool misc_enabled{};
//
//inline bool misc_unlimited_health{};
//inline bool misc_unlimited_ammo{};
//
//inline bool misc_rapidfire{};
//inline float misc_rapidfire_delay{};
//
//inline bool aim_enabled{};


inline int selected_tab{};
inline ImVec2 btn_size;

namespace Menu
{
	void Tabs(std::unordered_map<int, std::string> btns);
	void Render(int width, int height);
}