#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(lightColor);

    vec3 ambient = ambientStrength * vec3(lightColor);

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(lightColor); 
    
    vec4 mixedTexture = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);
    
    vec3 lighting = ambient + diffuse + specular;
    vec4 result = vec4(lighting, 1.0) * mixedTexture;
    
    FragColor = result;
}