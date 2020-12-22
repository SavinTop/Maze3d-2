#version 330 core
out vec4 FragColor;

in vec2 texC;
in vec3 normal;
in vec3 fragPos;
in mat3 TBN;
in vec4 FragPosLightSpace;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_height1;
uniform sampler2D texture_normal1;
uniform sampler2D shadowMap;

uniform vec3 lightDir;
uniform vec3 viewPos;
uniform bool showShadows;
uniform bool showLight;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    if(projCoords.z > 1.0)
        return 0;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
     
    float bias = 0;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    const int halfsize = 1;
    for(int x = -halfsize; x <= halfsize; ++x)
    {
        for(int y = -halfsize; y <= halfsize; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
}
shadow /= 9.0;

    return shadow;
}  

void main()
{
    float ambient = 0.6;
    vec3 color = texture(texture_diffuse1, texC).rgb;
    if(showLight)
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

    float shadow = 0;
    if(showShadows)
        shadow = ShadowCalculation(FragPosLightSpace);  
    vec3 result = (ambient+ (1.0 - shadow) *(diff+specular)) * color;
    FragColor =  vec4(result,1.0);
    } else{
        float shadow = 0;
        if(showShadows)
            shadow = ShadowCalculation(FragPosLightSpace);  
        vec3 result = (ambient+(1.0 - shadow)) * color;
        FragColor =  vec4(result,1.0);
    }
}