#version 330 core

in vec2 vo_tex;
in vec4 vo_color;

out vec4 fo_color;

uniform sampler2D texture0;

void main()
{
    fo_color = texture(texture0, vo_tex);
    // fo_color = vo_color;
}
