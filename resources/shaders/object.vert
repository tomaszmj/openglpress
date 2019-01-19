#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinatesIn;

out vec3 transformedNormal;
out vec3 transformedPosition;
out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0f);
//    transformedNormal = vec3(model * vec4(normal, 1.0));
    transformedNormal = normal;
    transformedPosition = vec3(model * vec4(position, 1.0));
    textureCoordinates = textureCoordinatesIn;
}
