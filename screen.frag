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

//const float offset = 9.0 / 300.0;  
//
//void main()
//{
//    vec2 offsets[9] = vec2[](
//        vec2(-offset,  offset), // 좌측 상단
//        vec2( 0.0f,    offset), // 중앙 상단
//        vec2( offset,  offset), // 우측 상단
//        vec2(-offset,  0.0f),   // 좌측 중앙
//        vec2( 0.0f,    0.0f),   // 정중앙
//        vec2( offset,  0.0f),   // 우측 중앙
//        vec2(-offset, -offset), // 좌측 하단
//        vec2( 0.0f,   -offset), // 중앙 하단
//        vec2( offset, -offset)  // 우측 하단   
//    );
//
//    float kernel[9] = float[](
//        1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16  
//    );
//    
//    vec3 sampleTex[9];
//    for(int i = 0; i < 9; i++)
//    {
//        sampleTex[i] = vec3(texture(screenTexture, v_tex_pos.st + offsets[i]));
//    }
//    vec3 col = vec3(0.0);
//    for(int i = 0; i < 9; i++)
//        col += sampleTex[i] * kernel[i];
//    
//    FragColor = vec4(col, 1.0);
//}  