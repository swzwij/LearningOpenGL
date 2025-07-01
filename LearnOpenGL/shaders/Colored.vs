# version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 fPosition;
out vec3 fNormal;
out vec3 fColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 color;

void main()
{
	int scale = 2;
	float roundedX = round((position.x * scale + 0.5) / scale);
	float roundedY = round((position.y * scale + 0.5) / scale);
	float roundedZ = round((position.z * scale + 0.5) / scale);

	vec3 roundedPosition = vec3(roundedX, roundedY, roundedZ);

	gl_Position = projection * view * model * vec4(roundedPosition, 1.0);
	
	fPosition = vec3(model * vec4(roundedPosition, 1.0));
	fNormal = mat3(transpose(inverse(model))) * normal;
	fColor = color;
}