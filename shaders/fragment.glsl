#version 330 core
out vec4 FragColor;
  
in vec2 texCoord;

uniform sampler2D tex;
uniform vec3 lightColor;

void main()
{
    FragColor = texture(tex, texCoord) * vec4(lightColor, 1.0f);
} 