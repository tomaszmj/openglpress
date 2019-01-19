#version 330 core
in vec3 transformedNormal;
in vec3 transformedPosition;
in vec2 textureCoordinates;
out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 objectColor;

uniform sampler2D wood;

void main()
{
    vec3 directionToLight = lightPosition - transformedPosition;
    float diffuseCoefficient = max(dot(normalize(transformedNormal), normalize(directionToLight)), 0.0);
    float distanceCoefficient = 0.7 / (dot(directionToLight, directionToLight) + 1.0);
    float diffuse = 0.1 * diffuseCoefficient;
    float ambient = 0.2;
    vec4 ownColor = texture(wood, textureCoordinates);
    color = (diffuse + ambient + distanceCoefficient) * vec4(lightColor, 1.0) * ownColor;
}
