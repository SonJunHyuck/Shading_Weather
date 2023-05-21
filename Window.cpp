#include "Window.h"

#include "Global_Variable.h"
#include "UtilityFunc.h"

using namespace Global_Variable;

Window::Window()
{
	glfw_window = NULL;
	window_width = 1920;
	window_height = 1080;
	this->title = "OpenGL_WINDOW";
	isFullscreen = false;
}

Window::Window(int width = 1920, int heignt = 1080, const char* title = "OpenGL_Window")
{
	glfw_window = NULL;
	window_width = width;
	window_height = heignt;
	this->title = title;
	isFullscreen = false;
}

Window::~Window()
{
}

// Window
int Window::Create_Window()
{
	// window�� �̹� ���� �Ǿ��ִ� -> �ı�
	if (glfw_window)
		glfwDestroyWindow(glfw_window);

	glfwDefaultWindowHints();

	// window ����
	if (isFullscreen)
		glfw_window = glfwCreateWindow(1920, 1080, title, glfwGetPrimaryMonitor(), NULL);
	else
		glfw_window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);

	if (glfw_window)
	{
		// OpenGL�� ���¸ӽ��̴� -> ���� context�� �������־�� ��
		glfwMakeContextCurrent(glfw_window);

		glfwGetFramebufferSize(glfw_window, &window_width, &window_height);
	}
	else
	{
		glfwTerminate();

		exit(EXIT_FAILURE);
	}

	return 1;
}

void Window::Set_Size(int width, int height)
{
	window_width = width;
	window_height = height;
}

void Window::Set_Buffer()
{
	Set_Board();
	Set_Particle();
}


// Object
void Window::Set_Board()
{
	checkerdBoard = new CheckerdBoard(glm::vec2(30, 10));
}

void Window::Set_Particle()
{
	particleEffect = new ParticleEffect();
	
	texture_id = Load_Texture("Particle-Texture.png");
	if (texture_id == -1)
	{
		std::cout << "Fail Texture Loading" << std::endl;
		texture_id = 0;

	}
	else
	{
		std::cout << "Success Texture Loading" << std::endl;
	}
}

void Window::Emit_Particle(int count, glm::vec2 position, glm::vec2 velocity)
{
	particleEffect->Emit_Particle(count, position, velocity);
}

// Render
void Window::Update()
{
	checkerdBoard->Update();
	particleEffect->Update_Particle();
}

void Window::Render()
{
	// ���ȭ�� �� �ʱ�ȭ
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ������Ʈ�� ��ġ�� ��� �ڿ� �ִ� ��ü�� ������ �ʰ�
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);									 // Enable Blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   // Type Of Blending To Perform

	glViewport(0, 0, window_width, window_height);  // ȭ�� 4��� �� ���� ��ܿ� ��Ŀ ����Ʈ
		
	checkerdBoard->Draw();

	particleEffect->Render();
}