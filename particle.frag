#version 430

in vec2 v_particle_pos;

out vec4 FragColor;

uniform sampler2D wind_texture;
uniform vec2 wind_min;
uniform vec2 wind_max;
uniform sampler2D u_color_ramp;

void main() 
{
    vec2 velocity = mix(wind_min, wind_max, texture2D(wind_texture, v_particle_pos).rg);
    float speed_t = length(velocity) / length(wind_max);

    // color ramp is encoded in a 16x16 texture
    vec2 ramp_pos = vec2(
        fract(16.0 * speed_t),
        floor(16.0 * speed_t) / 16.0);

    //FragColor = vec4(1, 0, 1, 1);
    FragColor = vec4(1, 1, 0, 1);
}