#include <iostream>
#include <array>
#include <thread>
#include <chrono>
#include "memory.h"
#include "offsets.h"
#include "miscellaneous.h"
#include "entity.h"
#include "maths.h"
#include "vector.h"
#include "aimbot.h"
#include "esp.h"

#include "GLCommon.h"
//#include "imgui.h"
//#include "imgui_impl_glfw.h"
//#include "imgui_impl_opengl3.h"


namespace Options
{
	//miscellaneous
	bool b_enable_unlimited_health{};
	bool b_enable_unlimited_ammo{};
	bool b_enable_rapidfire{};

	//debug
	bool b_enable_debug{};

	//aimbot
	bool b_enable_aimbot{};

	//esp
	bool b_enable_snaplines{};
	bool b_enable_triangles{};

}
using namespace std::chrono_literals;

Entity myself;
Miscellaneous misc{};
ESP visuals;

std::array<Entity, 32> entities{};
size_t current_entities;

void handle_input()
{
	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{
			Options::b_enable_unlimited_health = !Options::b_enable_unlimited_health;
		}
		if (GetAsyncKeyState(VK_DELETE) & 1)
		{
			Options::b_enable_unlimited_ammo = !Options::b_enable_unlimited_ammo;
		}
		if (GetAsyncKeyState(VK_DOWN) & 1)
		{
			Options::b_enable_rapidfire = !Options::b_enable_rapidfire;
		}
		if (GetAsyncKeyState(VK_UP) & 1)
		{
			Options::b_enable_aimbot = !Options::b_enable_aimbot;
		}
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			Options::b_enable_debug = !Options::b_enable_debug;
		}
		if (GetAsyncKeyState(VK_RCONTROL) & 1)
		{
			Options::b_enable_snaplines = !Options::b_enable_snaplines;
		}
		if (GetAsyncKeyState(VK_TAB) & 1)
		{
			Options::b_enable_triangles = !Options::b_enable_triangles;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(5));
	}
}

void debug_mode()
{
	while (true)
	{
		if (Options::b_enable_debug)
		{
			std::cout << "---DEBUG MODE---\n\n";
			for (size_t i{}; i < current_entities; ++i)
			{
				std::cout << std::hex;
				std::cout << "address: 0x" << entities[i].m_address << "\n";
				std::cout << "vTable: 0x" << entities[i].vf_table << "\n";
				std::cout << std::dec;
				std::cout << "name: " << entities[i].m_name << "\n";
				std::cout << "health: " << entities[i].m_health << "\n";
				std::cout << "is alive: " << entities[i].isAlive() << "\n";
				std::cout << "team: " << entities[i].m_team << "\n";

				std::cout << "coords: (" << entities[i].m_coords.x << ", "
					<< entities[i].m_coords.y << ", "
					<< entities[i].m_coords.z << ")\n";

				std::cout << "distance from local player: " << entities[i].m_distance_from_local_player << "\n";
				std::cout << "---------------------------------------\n";
			}
			std::this_thread::sleep_for(2ms);
			system("cls");
		}
	}
}

void miscellaneous()
{
	while (true)
	{
		if (myself.vf_table == offsets::vf_table_player)
		{
			if (Options::b_enable_unlimited_health)
			{
				misc.unlimited_health(myself.m_address);
			}
			if (Options::b_enable_unlimited_ammo)
			{
				misc.unlimited_ammo(myself.m_address);
			}
			if (Options::b_enable_rapidfire)
			{
				misc.rapidfire(myself.m_address);
			}
		}
		std::this_thread::sleep_for(std::chrono::microseconds(5));
	}
}


void aimbot_and_populate_sort()
{
	while (true)
	{
		if (current_entities > 0)
		{
			populate_entity_array(entities, myself, current_entities);
			Maths::bubble_sort(entities, current_entities);

			if (Options::b_enable_aimbot)
			{
				Aimbot::closest_target(get_closest_entity(entities, current_entities), myself);
			}
		}
		std::this_thread::sleep_for(5ms);
	}
}

void overlay(GLFWwindow* window)
{
	RECT rect;
	while (true)
	{
		HWND game_window = FindWindowA(nullptr, "AssaultCube");
		if (!game_window)
		{
			std::cout << "failed to get game window handle\n";
			return;
		}

		GetWindowRect(game_window, &rect);

		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;

		glfwSetWindowPos(window, rect.left, rect.top);
		glfwSetWindowSize(window, width, height);

		std::this_thread::sleep_for(5ms);
	}
}


void helper()
{
	while (true)
	{
		current_entities = offsets::get_max_entities() - 1 /*except me*/;
		update_local_player(myself);
		visuals.matrix = offsets::get_view_matrix();

		std::this_thread::sleep_for(5ms);
	}
}

int main()
{
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


	std::thread thread_handle_input(handle_input);
	thread_handle_input.detach();

	std::thread thread_overlay(overlay, window);
	thread_overlay.detach();

	std::thread thread_misc(miscellaneous);
	thread_misc.detach();

	std::thread thread_aimbot_and_populate_and_sort(aimbot_and_populate_sort);
	thread_aimbot_and_populate_and_sort.detach();

	std::thread thread_debug_mode(debug_mode);
	thread_debug_mode.detach();

	std::thread thread_helper(helper);
	thread_helper.detach();

	while (!glfwWindowShouldClose(window))
	{
		//RENDERING
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClear(GL_COLOR_BUFFER_BIT);

		if (Options::b_enable_snaplines)
		{
			visuals.draw_lines(current_entities, entities, myself, display_w, display_h);
		}

		if (Options::b_enable_triangles)
		{
			visuals.draw_boxes(current_entities, entities, myself, display_w, display_h);
			visuals.draw_health(current_entities, entities, display_w, display_h);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}