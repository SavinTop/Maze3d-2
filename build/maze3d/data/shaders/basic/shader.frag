#version 330 core
out vec4 FragColor;

in vec2 texC;
in vec3 normal;
in vec3 fragPos;
in mat3 TBN;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 tnormal = texture(texture_normal1, texC).rgb;
    tnormal = normalize(tnormal * 2.0 - 1.0);
    tnormal = normalize(TBN * tnormal);

    const float specularStrength = 0.5;
    vec3 lightDir = normalize(lightPos - fragPos);
    vec3 norm = normalize(tnormal);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec; 

    float diff = max(dot(norm,lightDir),0.0);

    float ambient = 0.2;
    float result = (ambient+diff+specular);
    FragColor = texture(texture_diffuse1, texC)* vec4(vec3(result),1.0);
}