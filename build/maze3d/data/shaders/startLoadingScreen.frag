#version 330 core
out vec4 FragColor;

in vec2 texC;
uniform sampler2D texture_diffuse1; 
uniform float loadingProgress;

void main()
{
    
    FragColor = vec4(1.0);
    
}