#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoordinatesIn;

out vec3 transformedNormal;
out vec3 transformedPosition;
out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 transform;
uniform float rmax;
uniform float crushing_factor;

void main()
{
    float crushing_coefficient = 2 * rmax + position.y * position.y * (4.0 - 8.0*rmax);
    vec3 crushed_position = vec3(position.x * crushing_coefficient , position.y, position.z * crushing_coefficient);
    gl_Position = transform * vec4(crushed_position, 1.0f);
    if(normal.y != 0.0f) // cylinder base
        transformedNormal = normal;
    else // curved surface - new normal vector needs to be calculated
    {
        float tangens = (8 - 16*rmax) * position.y; // derivative of surface equation
        float normal_r = 1 / (sqrt(tangens*tangens + 1));
        float normal_y = - tangens * normal_r;
        transformedNormal = normalize(vec3(normal.x * normal_r, normal_y, normal.z * normal_r));
    }
    transformedPosition = vec3(model * vec4(crushed_position, 1.0));
    textureCoordinates = textureCoordinatesIn;
}
