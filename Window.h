#pragma once

#include <iostream>
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "Viewer.h"

#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/matrix_inverse.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/glm/gtx/string_cast.hpp"
#include "include/glm/mat4x4.hpp"

#include "Loader.h"
#include "CheckerdBoard.h";
#include "ParticleEffect.h"

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "lib/glew32.lib")
#pragma comment(lib, "lib/glfw3.lib")

class Window
{
public :
	Window();
	Window(int width, int heignt, const char* title);
	~Window();
	int Create_Window();
	void Set_Size(int width, int height);
	void Set_Buffer();
		   
	void Set_Board();

	void Set_Particle();
	void Emit_Particle(int count, glm::vec2 position = glm::vec2(0), glm::vec2 velocity = glm::vec2(0));

	void Update();
	void Render();

	// get
	GLFWwindow* Get_GLFWwindow() { return glfw_window; };
private :
	GLFWwindow* glfw_window = NULL;
	const char* title;
	bool isFullscreen;
	
	CheckerdBoard* checkerdBoard;
	ParticleEffect* particleEffect;
};