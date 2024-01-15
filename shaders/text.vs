#version 330 core

layout (location = 0) in vec2 vi_pos;
layout (location = 1) in vec2 vi_tex;

out vec2 vo_tex;
out vec4 vo_color;

void main()
{
    gl_Position = vec4(vi_pos, 0.0, 0.0);
    vo_tex = vi_tex;
    vo_color = vec4(0.0, 0.5, 0.0, 1.0);
}
