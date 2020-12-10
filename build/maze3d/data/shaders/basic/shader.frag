#version 330 core
out vec4 FragColor;

in vec2 texC;
in vec3 normal;
in vec3 fragPos;
in mat3 TBN;
in vec4 FragPosLightSpace;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D shadowMap;

uniform vec3 lightDir;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}  

void main()
{
    vec3 tnormal = texture(texture_normal1, texC).rgb;
    tnormal = normalize(tnormal * 2.0 - 1.0);
    tnormal = normalize(TBN * tnormal);

    const float specularStrength = 1.0;
    //vec3 lightDir = normalize(lightPos - fragPos);
    vec3 norm = normalize(tnormal);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
    float specular = specularStrength * spec; 

    float diff = max(dot(norm,lightDir),0.0);

    float ambient = 0.4;
    float shadow = 0.0;//ShadowCalculation(FragPosLightSpace);  
    float result = (ambient+ (1.0 - shadow) *(diff+specular));
    FragColor = texture(texture_diffuse1, texC)* vec4(vec3(result),1.0);
}