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
    transformedNormal = normal; // I do not use rotations nor scales (in cube and cylinder) that would change normal vector
    transformedPosition = vec3(model * vec4(position, 1.0));
    textureCoordinates = textureCoordinatesIn;
}
