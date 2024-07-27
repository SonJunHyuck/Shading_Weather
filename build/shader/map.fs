#version 430

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
    vec4 col = texture(tex, TexCoords);

    // force color set map line
    if(col.a > 0.01)
        col = vec4(1, 1, 1, 1);
    else
        col = vec4(1, 1, 1, 0);
    
    FragColor = col;
} 