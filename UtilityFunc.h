#pragma once

// =========> include system
#include <iostream>
#include <vector>
#include "include/glm/glm.hpp"
#include "include/GL/glew.h"
#include "include/GLFW/glfw3.h"

#include "include/glm/gtc/matrix_transform.hpp"
#include "include/glm/gtc/matrix_inverse.hpp"
#include "include/glm/gtc/type_ptr.hpp"
#include "include/glm/gtx/string_cast.hpp"
#include "include/glm/mat4x4.hpp"

#include "Loader.h"
#include "Global_Variable.h"

glm::mat4 LookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up);

glm::mat4 Perspective(float fovy, float aspect, float _near, float _far);

glm::mat4 Orthographic(float left, float right, float top, float bottom, float _near, float _far);

glm::mat4 Orthographic(float width, float height, float _near, float _far);

GLuint Create_Texture(GLfloat filter, const void* data, int width, int height);

GLuint Load_Texture(const char* file_name);

GLuint Get_Uniform_Location(ShaderProgram* shader, const char* uniform_name);

int readFile(char* name, GLchar** buffer);

GLuint Load_Shader(const char* shader, int type);

GLuint Load_Shaders(char* vertexShader, char* fragmentShader, char* geometryShader);

GLuint Load_ComputeShader(const char* computeShader);
