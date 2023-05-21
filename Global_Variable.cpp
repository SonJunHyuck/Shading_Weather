#include "Global_Variable.h"

static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };
static float SPOT_LIGHT_ROTATE_ANGLE = 0.0f;

namespace Global_Variable
{
	glm::vec3 one = glm::vec3(1, 1, 1);
	glm::vec3 zero = glm::vec3(0, 0, 0);

	glm::vec3 eye;
	glm::vec3 look;
	glm::vec3 up;

	int window_width;
	int window_height;

	double delta = 0;
	double current_time = 0;
	double last_time = 0;
	int frame = 0;
	float seconds = 0;
	GLuint texture_id = 0;
	
	Viewer* viewer;

	std::vector<GLuint> textures = std::vector<GLuint>();

	void Init_Viewer()
	{
		float aspect = ((float)window_width / (float)window_width);
		glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
		glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
		glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);
		viewer = new Viewer(viewPoint, viewCenter, upVector, 45.0f, aspect);
	}

	void Update_Time()
	{
		current_time = glfwGetTime();

		delta = current_time - last_time;

		last_time = current_time;
		
		frame++;
		seconds += delta;

		if (seconds >= 1.0f)
		{
			//Display_FrameInfo();
			seconds = 0;
			frame = 0;
		}
	}

	void Update_Viewer()
	{
		eye = viewer->getViewPoint();
		look = viewer->getViewCenter();
		up = viewer->getUpVector();
	}
}
