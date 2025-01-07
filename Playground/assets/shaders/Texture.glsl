#type vertex
#version 330 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_TexCoord;

uniform mat4 u_ProjectionView;
uniform mat4 u_Model;

out vec2 v_TexCoord;

void main()
{
	v_TexCoord = a_TexCoord;
	gl_Position = u_ProjectionView * u_Model * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location=0) out vec4 a_FragColor;

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform float u_TileFactor;
uniform sampler2D u_Texture;

void main()
{
	a_FragColor = texture(u_Texture, v_TexCoord * u_TileFactor) * u_Color;
}