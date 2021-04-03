#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform vec2 position;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = vec4(vertex.x + position.x, vertex.y + position.y, 0.0, 1.0);
}