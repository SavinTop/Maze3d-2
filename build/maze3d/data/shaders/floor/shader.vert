#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;  

out vec2 texC;
out vec3 normal;
out vec3 fragPos;
out mat3 TBN;
out vec4 FragPosLightSpace;
out vec4 countOfShadows_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;
uniform sampler2D lightSpaceMatrixArray[50];
uniform int countOfShadows;

void main()
{
    mat3 tiModel = mat3(transpose(inverse(model)));
    normal = tiModel  * aNormal;

    vec3 T = normalize(vec3(tiModel  * aTangent));
    vec3 B = normalize(vec3(tiModel  * aBitangent)); 
    vec3 N = normalize(vec3(tiModel  * aNormal));

    TBN = mat3(T,B,N);

    fragPos = vec3(model * vec4(aPos,1.0));
    texC = aTexCoord;
    FragPosLightSpace = lightSpaceMatrix * vec4(fragPos, 1.0);
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    countOfShadows_out = countOfShadows;
}