#version 450 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
out vec4 fragColor;




void main()
{
        gl_Position = projection * view * model * vec4(pos.xyz,1.0);
        fragColor = color;

}

