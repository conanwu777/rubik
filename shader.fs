#version 400 core
flat in vec3 fColor;

out vec4 Color;

void main()
{
    Color = vec4(fColor, 1.0);
}
