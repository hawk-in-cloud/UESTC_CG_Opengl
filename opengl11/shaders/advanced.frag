#version 330 core

out vec4 FragColor;  // 最终输出的颜色

in vec2 TexCoords;  // 从顶点着色器传递的纹理坐标
in vec3 FragPos;  // 从顶点着色器传递的片段位置
in vec3 Normal;  // 从顶点着色器传递的法线

uniform sampler2D texture1;  // 纹理采样器
uniform vec3 lightPos;  // 光源位置
uniform vec3 viewPos;  // 观察者（相机）位置
uniform vec3 lightColor;  // 光源颜色
uniform vec3 objectColor;  // 物体颜色

void main()
{
    // 环境光：一个常数值（可以调节）表示光源对物体的基本照明
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // 漫反射：计算光源方向与法线之间的夹角
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // 高光反射：使用镜面反射模型
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // 镜面反射的亮度
    vec3 specular = specularStrength * spec * lightColor;

    // 纹理采样
    vec4 texColor = texture(texture1, TexCoords);

    // 合成最终颜色：环境光、漫反射和高光反射的叠加
    vec3 result = (ambient + diffuse + specular) * objectColor * texColor.rgb;

    FragColor = vec4(result, 1.0);
}
