#version 430

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    vec4 col = texture(tex, TexCoords);

    // force color set map line
    if(col.w > 0.01)
        col = vec4(1, 1, 1, 1);

    FragColor = col;
} 