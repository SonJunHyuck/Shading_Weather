#version 430

out vec4 FragColor;

in vec2 v_tex_pos;

uniform sampler2D screenTexture;
uniform float alpha;

void main()
{
    vec4 color = texture2D(screenTexture, v_tex_pos);
    
    gl_FragColor = vec4(color.xyz, alpha);
} 