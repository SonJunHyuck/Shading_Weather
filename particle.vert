#version 430

layout (location = 0) in float particle_index;
layout (location = 1) in vec2 v_position;

uniform sampler2D particle_texture;
uniform float particle_res;

out vec2 v_particle_pos;

void main()
{
    // 파티클 위치 설정
    vec4 color = texture2D(particle_texture, vec2(
        fract(particle_index / particle_res), floor(particle_index / particle_res) / particle_res));

    v_particle_pos = vec2(
        color.r / 255.0 + color.b,
        color.g / 255.0 + color.a);
        
	gl_Position = vec4(v_position, 0, 1);
}