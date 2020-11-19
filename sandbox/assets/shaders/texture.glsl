// shader for textures

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec4 a_color;

uniform mat4 u_viewProjection;

out vec2 v_texCoord;
out vec4 v_color;

void main() 
{
    v_texCoord = a_texCoord;
    v_color = a_color;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_texCoord;
in vec4 v_color;

// uniform sampler2D u_texture;
// uniform float u_tilingFactor;

void main() 
{
    //color = texture(u_texture, v_texCoord * u_tilingFactor) * u_color;

    color = v_color;
}
