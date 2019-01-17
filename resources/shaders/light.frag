#version 330 core
in vec3 transformedNormal;
in vec3 transformedPosition;
out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 objectColor;

void main()
{
    vec3 directionToLight = normalize(lightPosition - transformedPosition);
    float diffuseCoefficient = max(dot(normalize(transformedNormal), directionToLight), 0.0);
    float diffuse = 0.9 * diffuseCoefficient;
    float ambient = 0.1;
    color = vec4((diffuse + ambient) * lightColor * objectColor, 1.0);
}
