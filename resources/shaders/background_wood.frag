#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform sampler2D wood;

void main()
{
	color = texture(wood, TexCoord) * vec4(1.0, 1.0, 1.0, 1.0);
}
