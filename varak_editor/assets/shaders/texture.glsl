// shader for textures

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec4 a_color;
layout(location = 3) in float a_texIndex;
layout(location = 4) in float a_tilingFactor;

uniform mat4 u_viewProjection;

out vec2 v_texCoord;
out vec4 v_color;
out float v_texIndex;
out float v_tilingFactor;

void main() 
{
    v_texCoord = a_texCoord;
    v_color = a_color;
    v_texIndex = a_texIndex;
    v_tilingFactor = a_tilingFactor;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_texCoord;
in vec4 v_color;
in float v_texIndex;
in float v_tilingFactor;

uniform sampler2D u_textures[32];

void main() 
{
    vec2 texCoord = v_texCoord * v_tilingFactor;
    vec4 texColor = v_color;

    switch(int(v_texIndex))
	{
		case 0: texColor *= texture(u_textures[0], texCoord); break;
		case 1: texColor *= texture(u_textures[1], texCoord); break;
		case 2: texColor *= texture(u_textures[2], texCoord); break;
		case 3: texColor *= texture(u_textures[3], texCoord); break;
		case 4: texColor *= texture(u_textures[4], texCoord); break;
		case 5: texColor *= texture(u_textures[5], texCoord); break;
		case 6: texColor *= texture(u_textures[6], texCoord); break;
		case 7: texColor *= texture(u_textures[7], texCoord); break;
		case 8: texColor *= texture(u_textures[8], texCoord); break;
		case 9: texColor *= texture(u_textures[9], texCoord); break;
		case 10: texColor *= texture(u_textures[10], texCoord); break;
		case 11: texColor *= texture(u_textures[11], texCoord); break;
		case 12: texColor *= texture(u_textures[12], texCoord); break;
		case 13: texColor *= texture(u_textures[13], texCoord); break;
		case 14: texColor *= texture(u_textures[14], texCoord); break;
		case 15: texColor *= texture(u_textures[15], texCoord); break;
		case 16: texColor *= texture(u_textures[16], texCoord); break;
		case 17: texColor *= texture(u_textures[17], texCoord); break;
		case 18: texColor *= texture(u_textures[18], texCoord); break;
		case 19: texColor *= texture(u_textures[19], texCoord); break;
		case 20: texColor *= texture(u_textures[20], texCoord); break;
		case 21: texColor *= texture(u_textures[21], texCoord); break;
		case 22: texColor *= texture(u_textures[22], texCoord); break;
		case 23: texColor *= texture(u_textures[23], texCoord); break;
		case 24: texColor *= texture(u_textures[24], texCoord); break;
		case 25: texColor *= texture(u_textures[25], texCoord); break;
		case 26: texColor *= texture(u_textures[26], texCoord); break;
		case 27: texColor *= texture(u_textures[27], texCoord); break;
		case 28: texColor *= texture(u_textures[28], texCoord); break;
		case 29: texColor *= texture(u_textures[29], texCoord); break;
		case 30: texColor *= texture(u_textures[30], texCoord); break;
		case 31: texColor *= texture(u_textures[31], texCoord); break;
    }

    o_color = texColor;
}
