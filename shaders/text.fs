#version 330 core

in vec2 fragTexCoord;      // Interpolated texture coordinates per fragment

// Ouput data
out vec4 fragColor;

// Values that stay constant for the whole mesh.
uniform sampler2D texture0;  // Predefined texture sampler

void main()
{
    // Sample the texture at the interpolated coordinates
    vec4 texel = texture(texture0, fragTexCoord);

    // Output the color
    fragColor = texel;
}
