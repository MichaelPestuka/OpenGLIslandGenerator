#version 330 core
out vec4 FragColor;
  
in vec2 texCoord;
in float height;

uniform sampler2D tex;
uniform vec3 lightColor;

void main()
{
    //FragColor = texture(tex, texCoord) * vec4(lightColor, 1.0f);
    // FragColor = vec4(height, height, height, 1.0f);
    if(height < 0.4f)
    {
        FragColor = vec4(0.0f, 0.4f, 0.6f, 1.0f);
    }
    else if(height < 0.45f)
    {
        FragColor = vec4(0.75f, 0.69f, 0.5f, 1.0f);
    }
    else
    {
        FragColor = vec4(0.05f, 0.4f, 0.05f, 1.0f);
    }
} 