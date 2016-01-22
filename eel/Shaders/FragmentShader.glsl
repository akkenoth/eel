#version 330 core

layout(location = 0) out vec4 out_color; // To framebuffer, color location

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float timePassed;
uniform vec3 eyePosition;

uniform vec3 light0Position;
uniform vec3 light0Color;
uniform vec3 light1Position;
uniform vec3 light1Color;

uniform float materialShininess;
uniform float materialDiffusive;
uniform float materialSpecular;

uniform float attenuationConstant;
uniform float attenuationLinear;
uniform float attenuationQuadratic;

// From Vertex shader, preserve names!
in vec3 worldPosition;
in vec3 worldNormal;
in vec2 textureCoords;
in vec4 color;

void main(void) {
	// Base color and texture
	float timeOffset = timePassed * 0.1;
	vec4 color0 = texture(texture0, vec2(textureCoords.x, textureCoords.y));
	out_color = mix(color, color0, color0.a);
	vec4 color1 = texture(texture1, vec2(textureCoords.x, textureCoords.y - timeOffset));
	out_color = mix(out_color, color1, color1.a);

	// Lights
	vec3 view = normalize(eyePosition - worldPosition);

	vec3 light0 = normalize(light0Position - worldPosition);
	float distance0 = distance(light0Position, worldPosition);
	float attenuation0 = 1.0 / (attenuationConstant + distance0 * attenuationLinear + distance0 * distance0 * attenuationQuadratic);
	float diffuse0 = 0;
	float specular0 = 0;
	float lambert0 = dot(light0, worldNormal);
	if(lambert0 > 0.0) {
		diffuse0 = lambert0 * materialDiffusive;
		vec3 halfway = normalize(light0Position + worldPosition);
		specular0 = materialSpecular * pow(max(0, dot(halfway, worldNormal)), materialShininess);
	}
	float light0value = attenuation0 * (diffuse0 + specular0);
	vec3 light0out = light0Color * light0value;

	vec3 light1 = normalize(light1Position - worldPosition);
	float distance1 = distance(light1Position, worldPosition);
	float attenuation1 = 1.0 / (attenuationConstant + distance1 * attenuationLinear + distance1 * distance1 * attenuationQuadratic);
	float diffuse1 = 0;
	float specular1 = 0;
	float lambert1 = dot(light0, worldNormal);
	if(lambert1 > 0.0) {
		diffuse1 = lambert1 * materialDiffusive;
		vec3 halfway = normalize(light1Position + worldPosition);
		specular1 = materialSpecular * pow(max(0, dot(halfway, worldNormal)), materialShininess);
	}
	float light1value = attenuation1 * (diffuse1 + specular1);
	vec3 light1out = light1Color * light1value;

	vec3 light = light0 + light1;

	// light?
	// light = vec3(1.0);
	out_color = vec4(out_color.r * light.r, out_color.g * light.g, out_color.b * light.b, out_color.a);
}