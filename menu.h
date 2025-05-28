#pragma once

#include <Windows.h>
#include <unordered_map>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "settings.h"

inline int selected_tab{};
inline ImVec2 btn_size;

namespace Menu
{
	void Tabs(std::unordered_map<int, std::string> btns);
	void Render(int width, int height);
}