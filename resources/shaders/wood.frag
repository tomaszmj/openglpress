#version 330 core
in vec3 transformedNormal;
in vec3 transformedPosition;
in vec2 textureCoordinates;
out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

uniform sampler2D Texture;

void main()
{
    vec3 normal = normalize(transformedNormal);
    vec3 directionToObserver = normalize(cameraPosition - transformedPosition);
    vec3 directionToLight = normalize(lightPosition - transformedPosition);
    vec3 reflectedLightDirection = reflect(-directionToLight, normal);

    float specularCoefficient = pow(max(dot(directionToObserver, reflectedLightDirection), 0.0), 128);
    float diffuseCoefficient = 0.1 * max(dot(normal, directionToLight), 0.0);
    float ambientCoefficient = 0.4;

    vec4 ownColor = texture(Texture, textureCoordinates);
    color = (ambientCoefficient + diffuseCoefficient + specularCoefficient) * vec4(lightColor, 1.0) * ownColor;
}
