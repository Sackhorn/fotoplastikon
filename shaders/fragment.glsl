#version 330 core

// Ouput data
in vec3 Normal;
in vec3 TexCoords;
in vec3 FragPos;

uniform sampler2D albedo;
uniform vec3 lightPos;
out vec4 color;

void main()
{
	vec3 lightColor = vec3(1.0);
	float ambientStrenght = 0.1f;

	vec4 TexColor = texture(albedo, TexCoords.xy);
	vec3 norm = normalize(Normal);

	vec3 lightDir = normalize(lightPos-FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 ambient = ambientStrenght * lightColor;
	vec3 diffuse = diff * lightColor;

	vec4 result = TexColor * vec4((diffuse + ambient), 1.0);
	color = result;

//	color = vec4(1.0);
//	color = vec4(0.0, 1.0, 0.0, 1.0 );
}