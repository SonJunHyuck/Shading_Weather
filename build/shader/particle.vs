#version 430

//layout (location = 1) in vec2 particlePosition;
layout (location = 4) in vec2 particlePosition;
layout (location = 5) in vec4 tailColor;

out vec4 tail_color;

void main()
{
	tail_color = tailColor;

	gl_Position = vec4(particlePosition, 0, 1);
}