#version 450 core

out vec4 FragColor;

in vec4 objectColor;
uniform vec3 lightColor;

void main()
{
        FragColor = vec4(lightColor * objectColor.xyz, 1.0);
}



