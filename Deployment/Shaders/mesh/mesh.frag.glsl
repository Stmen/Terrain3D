#version 410 core

uniform sampler2D material;

out vec4 color;
in vec3 vertexNormal;
in vec2 tc;

void main()
{
	color = texture(material, tc);
	
	if (color.a <= 0.1)
		discard;
}