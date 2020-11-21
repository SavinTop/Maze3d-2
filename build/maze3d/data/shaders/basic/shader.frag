#version 330 core
out vec4 FragColor;

in vec2 texC;
in vec3 normal;
in vec3 fragPos;
uniform sampler2D texture_diffuse1; 

uniform vec3 lightPos;

void main()
{
    float lenToLight = length(lightPos - fragPos);

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm,lightDir),0.0);

    float ambient = 0.3;
    float result = (ambient+diff);
    FragColor = texture(texture_diffuse1, texC)* vec4(vec3(result),1.0);
}