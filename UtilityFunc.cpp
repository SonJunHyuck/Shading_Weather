
#pragma warning(disable : 4996)

#include "UtilityFunc.h"

// =========> include load texture
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// =========> exception variable
constexpr auto FAIL_TO_LOAD_TEXTURE = -1;

glm::mat4 LookAt(glm::vec3 campos, glm::vec3 look, glm::vec3 up)
{
	glm::mat4 matrix_LookAt = glm::mat4();
	glm::mat4 translation = glm::mat4();
	glm::mat4 rotation = glm::mat4();

	// translation matrix
	glm::vec4 v1 = glm::vec4(1, 0, 0, 0);
	glm::vec4 v2 = glm::vec4(0, 1, 0, 0);
	glm::vec4 v3 = glm::vec4(0, 0, 1, 0);
	glm::vec4 v4 = glm::vec4(-campos.x, -campos.y, -campos.z, 1);

	translation[0] = v1;
	translation[1] = v2;
	translation[2] = v3;
	translation[3] = v4;

	// 1. cam - target (camera는 - z축을 바라보고 있기 때문에 (-1) * (target - cam)
	glm::vec3 zaxis = glm::normalize(glm::vec3(campos - look));

	// 2. UpVector of camera 와 새로구한 z축의 외적 -> z축과 직교하는 또 하나의 축
	glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));

	// 미리 구한 2개의 축을 외적 -> 마지막 축
	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

	// transpose
	v1 = glm::vec4(xaxis[0], yaxis[0], zaxis[0], 0);
	v2 = glm::vec4(xaxis[1], yaxis[1], zaxis[1], 0);
	v3 = glm::vec4(xaxis[2], yaxis[2], zaxis[2], 0);
	v4 = glm::vec4(0, 0, 0, 1);

	rotation[0] = v1;
	rotation[1] = v2;
	rotation[2] = v3;
	rotation[3] = v4;

	matrix_LookAt = rotation * translation;

	return matrix_LookAt;
}

glm::mat4 Perspective(float fovy, float aspect, float _near, float _far)
{
	glm::mat4 matrix_perspective;
	float harf_fovy_radian = glm::radians(fovy / 2);

	glm::vec4 v1 = glm::vec4(1 / (aspect * tan(harf_fovy_radian)), 0, 0, 0);
	glm::vec4 v2 = glm::vec4(0, 1 / tan(harf_fovy_radian), 0, 0);
	glm::vec4 v3 = glm::vec4(0, 0, -((_far + _near) / (_far - _near)), -((2 * _far * _near) / (_far - _near)));
	glm::vec4 v4 = glm::vec4(0, 0, -1, 0);

	matrix_perspective[0] = v1;
	matrix_perspective[1] = v2;
	matrix_perspective[2] = v3;
	matrix_perspective[3] = v4;

	matrix_perspective = glm::transpose(matrix_perspective);

	return matrix_perspective;
}

glm::mat4 Orthographic(float left, float right, float top, float bottom, float _near, float _far)
{
	glm::mat4 matrix_Orthographic;
	float width = 2 * right;
	float height = 2 * top;

	/*matrix_Orthographic[0] = glm::vec4(2 * (right - left), 0, 0, 0);
	matrix_Orthographic[1] = glm::vec4(0, 2 * (top - bottom), 0, 0);
	matrix_Orthographic[2] = glm::vec4(0, 0, 2 * (far - near), 0);
	matrix_Orthographic[3] = glm::vec4(-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1);*/

	matrix_Orthographic[0] = glm::vec4(2 * (right - left), 0, 0, 0);
	matrix_Orthographic[1] = glm::vec4(0, 2 * (top - bottom), 0, 0);
	matrix_Orthographic[2] = glm::vec4(0, 0, 2 * (_far - _near), 0);
	matrix_Orthographic[3] = glm::vec4(-((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((_far + _near) / (_far - _near)), 1);

	matrix_Orthographic = glm::transpose(matrix_Orthographic);

	return matrix_Orthographic;
}

glm::mat4 Orthographic(float width, float height, float _near, float _far)
{
	glm::mat4 matrix_Orthographic;

	matrix_Orthographic[0] = glm::vec4(2 / width, 0, 0, 0);
	matrix_Orthographic[1] = glm::vec4(0, 2 / height, 0, 0);
	matrix_Orthographic[2] = glm::vec4(0, 0, -2 / (_far - _near), -(_far + _near) / (_far - _near));
	matrix_Orthographic[3] = glm::vec4(0, 0, 0, 1);

	matrix_Orthographic = glm::transpose(matrix_Orthographic);

	return matrix_Orthographic;
}

GLuint Create_Texture(GLfloat filter, const void* data, int width, int height)
{
	GLuint texture;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	return texture;
}

GLuint Load_Texture(const char* file_name)
{
	GLuint texture_id;
	
	glGenTextures(1, &texture_id);  //tex_2d is a member variable

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	int width, height, channel;
	unsigned char* image = stbi_load(file_name, &width, &height, &channel, 0);

	//std::cout << *image << std::endl;

	GLenum format;
	if (channel == 1)
		format = GL_RED;
	else if (channel == 3)
		format = GL_RGB;
	else if (channel == 4)
		format = GL_RGBA;

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "Success to load texture " << file_name << " : " << channel << std::endl;
		std::cout << "Success to load texture " << width << " : " << height << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture " << file_name << std::endl;
		texture_id = FAIL_TO_LOAD_TEXTURE;
	}

	stbi_image_free(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture_id;
}

GLuint Get_Uniform_Location(ShaderProgram* shader, const char* uniform_name)
{
	return shader->uniform(uniform_name);
}

int readFile(char* name, GLchar** buffer) {
	FILE* f = fopen(name, "rb");
	fseek(f, 0, SEEK_END);
	int pos = ftell(f);
	fseek(f, 0, SEEK_SET);

	(*buffer) = (GLchar*)malloc(pos + 1);
	fread(*buffer, pos - 1, 1, f);
	(*buffer)[pos - 1] = '\0';
	return fclose(f);
}

GLuint Load_Shader(const char* shader, int type)
{
	GLuint ShaderID = NULL;

	switch (type)
	{
	case 0:
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	case 1:
		ShaderID = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case 2:
		ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		ShaderID = glCreateShader(GL_VERTEX_SHADER);
		break;
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	/* Compile Vertex Shader */
	printf("Compiling Vertex shader\n");
	char* SourcePointer = NULL;
	readFile((char*)shader, &SourcePointer);

	glShaderSource(ShaderID, 1, (const GLchar**)&SourcePointer, NULL);
	glCompileShader(ShaderID);

	/* Check Vertex Shader */
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char* ShaderErrorMessage = (char*)calloc(InfoLogLength, sizeof(char));
	glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &(ShaderErrorMessage[0]));
	fprintf(stdout, "ShaderErrorMessage: %s\n", ShaderErrorMessage);

	return ShaderID;
}

GLuint Load_Shaders(char* vertexShader, char* fragmentShader, char* geometryShader) {

	GLint Result = GL_FALSE;
	int InfoLogLength;

	/* Create the shaders */
	GLuint VertexShaderID = Load_Shader(vertexShader, 0);
	GLuint FragmentShaderID = Load_Shader(fragmentShader, 1);
	GLuint GeometryShaderID = Load_Shader(geometryShader, 2);

	/*  Link the program */
	GLuint ProgramID = glCreateProgram();

	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glAttachShader(ProgramID, GeometryShaderID);

	glLinkProgram(ProgramID);

	/* Check the program */
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	char* programErrorMessage = (char*)calloc(InfoLogLength, sizeof(char));
	glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &(programErrorMessage[0]));
	fprintf(stdout, "programErrorMessage: %s\n", programErrorMessage);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	glDeleteShader(GeometryShaderID);

	return ProgramID;
}

GLuint Load_ComputeShader(const char* computeShader)
{
	/* Create the shaders */
	GLuint computeShaderID = glCreateShader(GL_COMPUTE_SHADER);

	GLint result = GL_FALSE;
	int infoLogLength;

	/* Compile Vertex Shader */
	printf("Compiling Compute shader\n");
	char* computeSourcePointer = NULL;
	readFile((char*)computeShader, &computeSourcePointer);

	glShaderSource(computeShaderID, 1, (const GLchar**)&computeSourcePointer, NULL);
	glCompileShader(computeShaderID);
	
	/* Check Vertex Shader */
	glGetShaderiv(computeShaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(computeShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* computeShaderErrorMessage = (char*)calloc(infoLogLength, sizeof(char));
	glGetShaderInfoLog(computeShaderID, infoLogLength, NULL, &(computeShaderErrorMessage[0]));
	fprintf(stdout, "computeShaderErrorMessage: %s\n", computeShaderErrorMessage);

	/*  Link the program */
	GLuint programID = glCreateProgram();

	glAttachShader(programID, computeShaderID);

	printf("Compute Shader ID: %d\n", computeShaderID);

	glLinkProgram(programID);

	/* Check the program */
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	char* programErrorMessage = (char*)calloc(infoLogLength, sizeof(char));
	glGetProgramInfoLog(programID, infoLogLength, NULL, &(programErrorMessage[0]));
	fprintf(stdout, "programErrorMessage: %s\n", programErrorMessage);

	glDeleteShader(computeShaderID);

	printf("Compute Shader Program ID: %d\n", programID);

	return programID;
}
