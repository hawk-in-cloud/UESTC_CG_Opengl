#version 330 core

in vec3 TexCoords;  // 来自顶点着色器的纹理坐标
out vec4 FragColor;  // 输出颜色

uniform samplerCube skybox;  // 天空盒纹理

void main()
{
    // 从天空盒纹理中采样颜色
    FragColor = texture(skybox, TexCoords);
}
