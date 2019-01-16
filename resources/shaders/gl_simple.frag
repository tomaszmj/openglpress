#version 330 core
in float outTmp;
out vec4 color;

void main()
{
	color = vec4(0.0, 0.0, outTmp, 1.0);
}
