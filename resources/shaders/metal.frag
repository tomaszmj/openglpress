#version 330 core
in vec3 transformedNormal;
in vec3 transformedPosition;
in vec2 textureCoordinates;
out vec4 color;

uniform vec3 lightColor;
uniform vec3 lightPosition;

uniform sampler2D Texture;

void main()
{
    vec3 directionToLight = normalize(lightPosition - transformedPosition);
    float diffuseCoefficient = max(dot(normalize(transformedNormal), directionToLight), 0.0);
    float diffuse = 0.9 * diffuseCoefficient;
    float ambient = 0.1;
    vec4 ownColor = texture(Texture, textureCoordinates);
    color = (diffuse + ambient) * vec4(lightColor, 1.0) * ownColor;
}
