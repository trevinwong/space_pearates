#version 330 core
layout (location = 0) in vec2 in_vertex;
layout (location = 1) in vec3 in_color;

out vec4 vertexColor;

uniform mat4 model;
uniform mat4 projection;

void main()
{
		vertexColor = vec4(in_color.xyz, 1.0);
    gl_Position = projection * model * vec4(in_vertex.xy, 0.0, 1.0);
}

