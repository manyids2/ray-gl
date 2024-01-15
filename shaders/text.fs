#version 330 core

in vec2 aTexCoord;

out vec4 finalColor;

uniform sampler2D texture0;

void main()
{
    // finalColor = texture(texture0, aTexCoord);
    finalColor = vec4(0.0, 0.5, 0.0, 1.0);
}
