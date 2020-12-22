#version 330 core
out vec4 FragColor;

in vec2 texC;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform float delta;

void main()
{
    FragColor = mix(texture(texture_diffuse1, texC),texture(texture_diffuse2, texC),delta);
}