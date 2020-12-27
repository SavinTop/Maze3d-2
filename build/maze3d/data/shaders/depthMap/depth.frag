#version 330 core
out vec4 FragColor;

in vec2 texC;

uniform sampler2D depthMap;

void main()
{             
    float depthValue = texture(depthMap, texC).r;
    //FragColor = vec4(vec3(depthValue), 1.0);
    FragColor = texture(depthMap, texC);
}