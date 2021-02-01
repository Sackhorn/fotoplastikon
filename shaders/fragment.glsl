#version 330 core
#define NR_POINT_LIGHTS 10
#define NR_SPOT_LIGHTS 10

struct BasicMaterial
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 color;
	vec3 direction;
};

struct PointLight
{
	vec3 color;
	vec3 position;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec3 color;
	vec3 position;
	vec3 direction;
	float lightAngle;
};

// Input data
in vec3 Normal;
in vec3 TexCoords;
in vec3 FragPos;

uniform sampler2D albedo;
uniform vec3 viewPos;
uniform BasicMaterial material;
uniform DirectionalLight directionLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform int pointLightsNmbr;
uniform int spotLightsNmbr;

// Output Data
out vec4 color;

//Calculates influence of Directional Light
vec4 CalcDirLights(vec3 normal, vec4 texture, vec3 viewDir)
{
	vec3 ambient = material.ambient * directionLight.color;
	vec3 lightDirection = normalize(directionLight.direction);
	float diff = max(dot(normal, lightDirection), 0.0);
	vec3 diffuse = diff * directionLight.color;

	//	We only calculate specular if diffuse is present, otherwise there is no light to make a specular
	vec3 specular = vec3(0.0);
	if(diff > 0.0f)
	{
		vec3 reflectDir = reflect(-lightDirection, normal);
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		specular = directionLight.color * (material.specular * spec);
	}

	return texture * vec4((diffuse + ambient + specular), 1.0);
}

vec4 CalcPointlights(vec3 normal, vec4 texture, vec3 viewDir)
{
	vec3 total_ambient = vec3(0.0), total_diffuse = vec3(0.0), total_specular = vec3(0.0);
	for(int i=0; i < pointLightsNmbr; i++)
	{
		PointLight light = pointLights[i];
		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);
		vec3 lightDirection = normalize(light.position - FragPos);

		vec3 ambient = material.ambient * light.color;
		float diff = max(dot(normal, lightDirection), 0.0);
		vec3 diffuse = diff * light.color;
		vec3 specular = vec3(0.0);
		if(diff > 0.0f)
		{
			vec3 reflectDir = reflect(-lightDirection, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			specular = light.color * (material.specular * spec);
		}
		total_ambient += ambient * attenuation;
		total_diffuse += diffuse * attenuation;
		total_specular += specular * attenuation;
	}

	return texture * vec4((total_ambient + total_diffuse + total_specular), 1.0);
}

vec4 CalcSpotlights(vec3 normal, vec4 texture, vec3 viewDir)
{
	vec3 total_ambient = vec3(0.0), total_diffuse = vec3(0.0), total_specular = vec3(0.0);
	for(int i=0; i < spotLightsNmbr; i++)
	{
		SpotLight light = spotLights[i];
		float distance = length(light.position - FragPos);
		vec3 lightDirection = normalize(FragPos - light.position);
		vec3 lightForward = normalize(light.direction);


		vec3 ambient = material.ambient * light.color;

		float diff = 0.0;
		if(dot(lightDirection, lightForward) > cos(radians(light.lightAngle)))
		{
			diff = max(dot(normal, -lightDirection), 0.0);
		}
		vec3 diffuse = diff * light.color;
		vec3 specular = vec3(0.0);
		if(diff > 0.0f)
		{
			vec3 reflectDir = reflect(-lightDirection, normal);
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
			specular = light.color * (material.specular * spec);
		}
		total_ambient += ambient;
		total_diffuse += diffuse;
		total_specular += specular;
	}
	return texture * vec4((total_ambient + total_diffuse + total_specular), 1.0);
}

void main()
{
	vec4 TexColor = texture(albedo, TexCoords.xy);
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec4 summary = vec4(0.0);
	summary += CalcDirLights(norm, TexColor, viewDir);
	summary += CalcPointlights(norm, TexColor, viewDir);
	summary += CalcSpotlights(norm, TexColor, viewDir);
	summary.w = 1.0;
	color = summary;
}