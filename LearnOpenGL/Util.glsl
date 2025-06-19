struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct DirectionalLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight 
{    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; 

vec3 CalculateDirectionalLight(DirectionalLight light, Material material, vec3 normal, vec2 TexCoords, vec3 viewDirection)
{
    vec3 lightDirection = normalize(-light.direction);
    
    float diff = max(dot(normal, lightDirection), 0.0);
    
    vec3 reflectDirection = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    
    return (ambient + diffuse + specular);
}  

vec3 CalculatePointLight(PointLight light, Material material, vec3 normal, vec2 TexCoords, vec3 fragPosition, vec3 viewDirection)
{
    vec3 lightDir = normalize(light.position - fragPosition);
    
    float diff = max(dot(normal, lightDir), 0.0);
    
    vec3 reflectDirection = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    
    float distance = length(light.position - fragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 