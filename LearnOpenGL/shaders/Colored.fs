#version 330 core

out vec4 FragColor;

in vec3 fPosition;
in vec3 fNormal;
in vec3 fColor;

void main()
{
    FragColor = vec4(fColor, 1.0);
}