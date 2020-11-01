#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 texC;
out vec3 lightPos;
out vec3 fragPos;
out vec3 normal;

uniform mat4 rotate;
uniform mat4 view;

void main()
{
    gl_Position = view * rotate * vec4(aPos, 1.0);
    lightPos = vec3(0, 0.5, -0.5);
    texC = aTexCoord;
    normal = mat3(transpose(inverse(rotate))) * aNormal;
    fragPos = vec3(rotate * vec4(aPos, 1.0));
}