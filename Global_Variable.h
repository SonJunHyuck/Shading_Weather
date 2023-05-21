#pragma once
#include <iostream>
#include <vector>
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"
#include "include/GL/glut.h"
#include "include/glm/glm.hpp"

#include "Viewer.h"

using namespace std;

namespace Global_Variable
{
	extern struct Particle
	{
		glm::vec2 position;
		float age;
		float life;
		glm::vec2 tail[];
	};

	extern glm::vec3 one;
	extern glm::vec3 zero;
	
	extern Viewer* viewer;
	extern glm::vec3 eye;
	extern glm::vec3 look;
	extern glm::vec3 up;

	extern int window_width;
	extern int window_height;
	
	extern double delta;
	extern double current_time;
	extern double last_time;
	extern int frame;
	extern float seconds;

	extern std::vector<GLuint> textures;

	void Init_Viewer();

	void Update_Time();
	void Update_Viewer();

	// Display Info
	inline void Display_GraphicInfo()
	{
		cout << "OpenGL version: " << glGetString(GL_VERSION) << endl; //8
		cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
		cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
		cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
	}
	inline void Display_FrameInfo()
	{

		printf("%f ms/frame  %d fps \n", 1000.0 / (double)frame, frame);
	}
}
