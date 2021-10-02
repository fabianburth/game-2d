#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 position, vec2 texCoords>

out vec2 TexCoords;

uniform vec2 position;
uniform vec4 size;

void main()
{
    TexCoords = vertex.zw;
    gl_Position = vec4(vertex.x * size.x  + size.z + position.x, vertex.y * size.y + size.w + position.y, 0.0, 1.0);
}