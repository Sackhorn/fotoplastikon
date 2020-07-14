#version 330 core

// Ouput data
in vec3 Normal;
in vec3 TexCoords;
uniform sampler2D albedo;
out vec4 color;

void main()
{
	color = texture(albedo, TexCoords.xy);
}