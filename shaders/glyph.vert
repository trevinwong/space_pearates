#version 330 core
layout (location = 0) in vec2 in_vertex;
layout (location = 1) in vec2 in_texCoord;

out vec2 texCoord;

uniform mat4 projection;

void main()
{
    texCoord = in_texCoord.xy;
    gl_Position = projection * vec4(in_vertex.xy, 0.0, 1.0);
}