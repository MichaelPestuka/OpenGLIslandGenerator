#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;
out float height;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
    height = aPos.y;
    if(aPos.y < 0.4f)
    {
        gl_Position = projection * view * model * vec4(aPos.x, 0.4f, aPos.z, 1.0); // see how we directly give a vec3 to vec4's constructor
    }
    else
    {
        gl_Position = projection * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    }
    texCoord = aTexCoord;
}