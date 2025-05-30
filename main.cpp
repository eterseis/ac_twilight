#include "pch.hpp"
#include "includes.hpp"

struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start{}, end{};
	std::chrono::duration<float> duration{};

	Timer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms{ duration.count() * 1000.0f };
		std::cout << "Timer took: " << ms << "ms\n";
	}
};

using namespace std::chrono_literals;

Miscellaneous misc;
ESP visuals;


void hide_menu(GLFWwindow* window)
{
	glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GL_TRUE);
	HWND ac_window = FindWindowA(nullptr, "AssaultCube");
	if (!ac_window)
	{
		std::cout << "failed to hide window\n";
		return;
	}
	EnableWindow(ac_window, true);
	SetForegroundWindow(ac_window);
	SetActiveWindow(ac_window);
	UpdateWindow(ac_window);
}

void show_menu(GLFWwindow* window)
{
	glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GL_FALSE);
	HWND ac_window = FindWindowA(nullptr, "AssaultCube");
	if (!ac_window)
	{
		std::cout << "failed to show window\n";
		return;
	}
	EnableWindow(ac_window, false);
	glfwFocusWindow(window);
	UpdateWindow(ac_window);
}

void handle_input(GLFWwindow* window)
{
	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Settings::enable_menu = !Settings::enable_menu;

			Settings::enable_menu ? show_menu(window) : hide_menu(window);
		}
		//panic key
		if (GetAsyncKeyState(VK_NUMPAD0))
		{
			glfwSetWindowShouldClose(window, true);
		}
		std::this_thread::sleep_for(std::chrono::microseconds(5));
	}
}

void miscellaneous()
{
	while (true)
	{
		if (Globals::myself.vf_table == offsets::vf_table_player)
		{
			if (Settings::misc_unlimited_health)
			{
				misc.unlimited_health(Globals::myself.m_address);
			}
			if (Settings::misc_unlimited_ammo)
			{
				misc.unlimited_ammo(Globals::myself.m_address);
			}
			if (Settings::misc_rapidfire)
			{
				misc.rapidfire(Globals::myself.m_address, Settings::misc_rapidfire_delay);
			}
		}
		std::this_thread::sleep_for(std::chrono::microseconds(5));
	}
}

void aimbot_and_populate_sort()
{
	while (true)
	{
		if (Globals::current_entities > 0)
		{
			populate_entity_array(Globals::entities, Globals::current_entities);
			Maths::bubble_sort(Globals::entities, Globals::current_entities);

			if (Settings::aim_enabled)
			{
				Aimbot::closest_target(Settings::aim_ignore_teammates, get_closest_entity(Settings::aim_ignore_teammates, Globals::entities, Globals::current_entities), Globals::myself);
			}
		}
		std::this_thread::sleep_for(1ms);
	}
}

void overlay(GLFWwindow* window)
{
	while (true)
	{
		HWND game_window = FindWindowA(nullptr, "AssaultCube");
		if (!game_window) continue;

		WINDOWINFO info;
		info.cbSize = sizeof(WINDOWINFO);

		GetWindowInfo(game_window, &info);


		int width = Globals::mem.Read<int>(Globals::moduleBase + offsets::game_resolution);
		int height = Globals::mem.Read<int>(Globals::moduleBase + offsets::game_resolution + 0x4);

		glfwSetWindowSize(window, width, height);
		glfwSetWindowPos(window, info.rcClient.left, info.rcClient.top);

		std::this_thread::sleep_for(1ms);
	}
}

void helper()
{
	while (true)
	{
		Globals::current_entities = offsets::get_max_entities() - 1 /*except me*/;
		update_local_player();
		visuals.m_matrix = offsets::get_view_matrix();

		std::this_thread::sleep_for(1ms);
	}
}

//void triggerbot()
//{
//	/*while (true)
//	{*/
//	if (Settings::aim_triggerbot)
//	{
//		INPUT inputs[2] = { };
//
//		inputs[0].type = INPUT_MOUSE;
//		inputs[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//
//
//		inputs[1].type = INPUT_MOUSE;
//		inputs[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
//
//		SendInput(1, inputs, sizeof(INPUT));
//		std::this_thread::sleep_for(1ms);
//		SendInput(1, &inputs[1], sizeof(INPUT));
//	}
//	//std::this_thread::sleep_for(5ms);
//	//}


int main()
{
	constexpr char glsl_version[]{ "#version 130" };
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	glfwWindowHint(GLFW_FLOATING, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, GL_TRUE);
	glfwWindowHint(GLFW_DECORATED, FALSE);

	GLFWwindow* window{ glfwCreateWindow(800, 600, "twilight", nullptr, nullptr) };

	if (!window)
	{
		std::cout << "Failed to create window.\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Failed to initialize GLEW\n";


	{
		std::thread thread_handle_input(handle_input, window);
		thread_handle_input.detach();

		std::thread thread_overlay(overlay, window);
		thread_overlay.detach();

		std::thread thread_misc(miscellaneous);
		thread_misc.detach();

		std::thread thread_aimbot_and_populate_and_sort(aimbot_and_populate_sort);
		thread_aimbot_and_populate_and_sort.detach();

		std::thread thread_helper(helper);
		thread_helper.detach();
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGuiStyle& style{ ImGui::GetStyle() };
	ImVec4* colors{ style.Colors };

	int width;
	int height;
	{
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
		colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.54f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.48f, 0.26f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.37f, 0.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.21f, 0.16f, 0.48f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(0.45f, 0.26f, 0.98f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.41f, 0.00f, 1.00f, 0.40f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.48f, 0.26f, 0.98f, 0.52f);
		colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.34f, 0.06f, 0.98f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.15f, 0.15f, 0.15f, 0.80f);
		colors[ImGuiCol_HeaderActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
		colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.13f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.38f, 0.38f, 0.38f, 1.00f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.26f, 0.98f, 0.50f);
		colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.20f, 0.58f, 0.73f);
		colors[ImGuiCol_TabSelected] = ImVec4(0.29f, 0.20f, 0.68f, 1.00f);
		colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_TabDimmed] = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
		colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
		colors[ImGuiCol_TabDimmedSelectedOverline] = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TableHeaderBg] = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
		colors[ImGuiCol_TableBorderStrong] = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
		colors[ImGuiCol_TableBorderLight] = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
		colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextLink] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.04f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavCursor] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);


		style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style.WindowPadding = ImVec2(4.0f, 4.0f);
		style.WindowRounding = 7.0f;
		style.FrameRounding = 3.0f;
		style.GrabMinSize = 20.0f;
		style.SeparatorTextBorderSize = 2.0f;
	}
	while (!glfwWindowShouldClose(window))
	{
		glfwGetWindowSize(window, &width, &height);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (Settings::enable_menu)
		{
			//ImGui::ShowDemoWindow();
			Menu::Render(width, height);
		}

		//RENDERING
		ImGui::Render();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Settings::visuals_enabled)
		{
			Timer t;

			visuals.m_ignore_teammates = Settings::visuals_ignore_teammates;
			visuals.m_outlined = Settings::visuals_outlined;
			visuals.m_display_w = display_w;
			visuals.m_display_h = display_h;


			if (Settings::visuals_snaplines)
			{
				visuals.snaplines(Settings::visuals_snaplines_color);
			}

			if (Settings::visuals_bounding_box)
			{
				visuals.bounding_box(Settings::visuals_filled_bounding_box, Settings::visuals_bounding_box_color);
			}

			if (Settings::visuals_health_bar)
			{
				visuals.health(Settings::visuals_health_bar_color);
			}
		}

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}