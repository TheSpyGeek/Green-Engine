#version 330

// input attributes
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertNormal;

uniform mat4 normalMatrix;


uniform mat4 modelMat;
uniform mat4 projMat;
uniform mat4 viewMat;

uniform mat4 lightMat4;
uniform vec4 light;

out vec4 normal;
out vec4 normalView;
out vec4 eyeView;
out vec4 vertex;

out vec4 lightVec;

void main() {

	vertex = vec4(position, 1.0);

	mat4 mv = viewMat * modelMat;

	gl_Position = projMat*mv*vec4(position, 1.0);


	normal = vec4(vertNormal,1.0);
	normalView = normalize(normalMatrix*normal);

	eyeView = normalize(mv*vec4(position,0.0));

	vec4 vertexPosition_cameraspace = mv*vec4(position, 1.0);

	lightVec = light;

	// gl_Position = projMat*vertexPosition_cameraspace;
	// normal = normalize(vec4(vertNormal,0.0));
	/*normal = vec4(vertNormal,1.0);
	normalView = normalize(normalMatrix*normal);
	eyeView = normalize(mv*vec4(position,0.0));*/

	/*mat4 normalMat = inverse(mv);
	normal = vec4(vertNormal,0);
	normalView = normalize(normalMat*normal);

	// normal = normalize(vec4(vertNormal,0.0));
	// normalView = normalize(normalMatrix*normal);
	eyeView = vec4(0) - vertexPosition_cameraspace;

	vec4 LightPosition_cameraspace = viewMat * light;
	vec4 LightDirection_cameraspace = LightPosition_cameraspace + eyeView;

	lightVec = LightDirection_cameraspace;*/
}
