#version 330 core
layout (location = 0) in vec4 vertexPosition;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
    TexCoord = vertexPosition.zw;
    gl_Position = projection * model * vec4(vertexPosition.xy, 0.0, 1.0);
}