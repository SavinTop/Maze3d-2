#version 330 core
out vec4 FragColor;

in vec2 texC;
uniform sampler2D texture_diffuse1; 

in vec3 lightPos;
in vec3 fragPos;
in vec3 normal;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - fragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    FragColor = texture(texture_diffuse1, texC);
}