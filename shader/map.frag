#version 430

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    vec4 col = texture2D(screenTexture, TexCoords);

    // 선을 하얗게 출력
    if(col.a > 0)
        col = vec4(1, 1, 1, 1);

    FragColor = col;
} 