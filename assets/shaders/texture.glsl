// shader for textures

#type vertex
#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_textureCoord;
layout(location = 2) in vec4 a_color;
layout(location = 3) in float a_textureIndex;
layout(location = 4) in float a_tilingFactor;

uniform mat4 u_viewProjection;

out vec2 v_textureCoord;
out vec4 v_color;
out float v_textureIndex;
out float v_tilingFactor;

void main() 
{
    v_textureCoord = a_textureCoord;
    v_color = a_color;
    v_textureIndex = a_textureIndex;
    v_tilingFactor = a_tilingFactor;

    gl_Position = u_viewProjection * vec4(a_position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 o_color;

in vec2 v_textureCoord;
in vec4 v_color;
in float v_textureIndex;
in float v_tilingFactor;

uniform sampler2D u_textures[32];

void main() 
{
    vec2 textureCoord = v_textureCoord * v_tilingFactor;
    vec4 textureColor = v_color;

    switch(int(v_textureIndex))
	{
		case 0: textureColor *= texture(u_textures[0], textureCoord); break;
		case 1: textureColor *= texture(u_textures[1], textureCoord); break;
		case 2: textureColor *= texture(u_textures[2], textureCoord); break;
		case 3: textureColor *= texture(u_textures[3], textureCoord); break;
		case 4: textureColor *= texture(u_textures[4], textureCoord); break;
		case 5: textureColor *= texture(u_textures[5], textureCoord); break;
		case 6: textureColor *= texture(u_textures[6], textureCoord); break;
		case 7: textureColor *= texture(u_textures[7], textureCoord); break;
		case 8: textureColor *= texture(u_textures[8], textureCoord); break;
		case 9: textureColor *= texture(u_textures[9], textureCoord); break;
		case 10: textureColor *= texture(u_textures[10], textureCoord); break;
		case 11: textureColor *= texture(u_textures[11], textureCoord); break;
		case 12: textureColor *= texture(u_textures[12], textureCoord); break;
		case 13: textureColor *= texture(u_textures[13], textureCoord); break;
		case 14: textureColor *= texture(u_textures[14], textureCoord); break;
		case 15: textureColor *= texture(u_textures[15], textureCoord); break;
		case 16: textureColor *= texture(u_textures[16], textureCoord); break;
		case 17: textureColor *= texture(u_textures[17], textureCoord); break;
		case 18: textureColor *= texture(u_textures[18], textureCoord); break;
		case 19: textureColor *= texture(u_textures[19], textureCoord); break;
		case 20: textureColor *= texture(u_textures[20], textureCoord); break;
		case 21: textureColor *= texture(u_textures[21], textureCoord); break;
		case 22: textureColor *= texture(u_textures[22], textureCoord); break;
		case 23: textureColor *= texture(u_textures[23], textureCoord); break;
		case 24: textureColor *= texture(u_textures[24], textureCoord); break;
		case 25: textureColor *= texture(u_textures[25], textureCoord); break;
		case 26: textureColor *= texture(u_textures[26], textureCoord); break;
		case 27: textureColor *= texture(u_textures[27], textureCoord); break;
		case 28: textureColor *= texture(u_textures[28], textureCoord); break;
		case 29: textureColor *= texture(u_textures[29], textureCoord); break;
		case 30: textureColor *= texture(u_textures[30], textureCoord); break;
		case 31: textureColor *= texture(u_textures[31], textureCoord); break;
    }

    o_color = textureColor;
}
