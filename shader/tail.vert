#version 430

layout (location = 2) in vec2 v_position;
layout (location = 5) in vec4 v_tail_color;

out vec4 tail_color;

void main()
{
	tail_color = v_tail_color;

	gl_Position = vec4(v_position, 0, 1);
}