#version 330 core

layout (location = 0) in vec3 aPos;  // 顶点位置
layout (location = 1) in vec3 aNormal;  // 顶点法线
layout (location = 2) in vec2 aTexCoords;  // 纹理坐标

out vec2 TexCoords;  // 传递给片段着色器的纹理坐标
out vec3 FragPos;  // 传递给片段着色器的片段位置
out vec3 Normal;  // 传递给片段着色器的法线

uniform mat4 model;  // 模型变换矩阵
uniform mat4 view;  // 视图变换矩阵
uniform mat4 projection;  // 投影变换矩阵

void main()
{
    // 计算传递给片段着色器的变量
    FragPos = vec3(model * vec4(aPos, 1.0));  // 当前片段的位置
    Normal = mat3(transpose(inverse(model))) * aNormal;  // 计算世界空间中的法线
    TexCoords = aTexCoords;  // 传递纹理坐标

    // 计算最终的顶点位置
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
