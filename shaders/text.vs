#version 330 core

// Input vertex data, different for all executions of this shader.
in vec3 vertexPosition;    // Vertex position (x, y, z)
in vec2 vertexTexCoord;    // Vertex texture coordinates (u, v)

// Output data; will be interpolated for each fragment.
out vec2 fragTexCoord;

void main()
{
    // Pass through the texture coordinates
    fragTexCoord = vertexTexCoord;

    // Transform the vertex position and output it
    gl_Position = vec4(vertexPosition, 1.0);
}
