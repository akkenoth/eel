#version 330 core
// Blinn-Phong shading with attenuation, soft cut-off for specular light and using energy conserving model
const float PI = 3.14159265;

layout(location = 0) out vec4 out_color; // To framebuffer, color location

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float timePassed;
uniform vec3 eyePosition;

uniform vec3 light0Position;
uniform vec3 light0Color;
uniform vec3 light1Position;
uniform vec3 light1Color;

uniform float materialAmbient;
uniform float materialDiffusive;
uniform float materialSpecular;
uniform float materialShininess;

uniform float attenuationConstant;
uniform float attenuationLinear;
uniform float attenuationQuadratic;

// From Vertex shader, preserve names!
in vec3 worldPosition;
in vec3 worldNormal;
in vec2 textureCoords;
in vec4 color;

void calculateLight(in vec3 lightPosition, in vec3 lightColor, inout vec3 diffuseSum, inout vec3 specularSum, in bool blinn) {
	// Direction TO viewer and light
	vec3 viewDirection = normalize(eyePosition - worldPosition);
	vec3 lightDirection = normalize(lightPosition - worldPosition);
	float lambertian = dot(worldNormal, lightDirection);
	// We're interested in this light source only if angle <= +-90deg
	float d = distance(lightPosition, worldPosition);
	float attenuation = 1.0 / (attenuationConstant + d * attenuationLinear + d * d * attenuationQuadratic);
		
	if(lambertian > 0.0) {
		diffuseSum += attenuation * lightColor * materialDiffusive * lambertian;
	}

	vec3 reflectDirection;
	float energyCoefficient;
	if(blinn) {
		// Blinn-Phong
		energyCoefficient = (8.0 + materialShininess) / (8.0 * PI);
		// halfway between direction to light and to viewer
		reflectDirection = normalize(lightDirection + viewDirection);
	} else {
		// Phong
		energyCoefficient = (2.0 + materialShininess) / (2.0 * PI);
		// Straight reflection
		reflectDirection = reflect(-lightDirection, worldNormal);
	}
	float angle = dot(worldNormal, reflectDirection);
	if(angle > 0.0) {
		specularSum += attenuation * lightColor * materialSpecular * energyCoefficient * pow(angle, materialShininess * 4.0);
	}
}

void main(void) {
	// Base color and texture
	float timeOffset = timePassed * 0.1;
	vec4 color0 = texture(texture0, vec2(textureCoords.x, textureCoords.y));
	out_color = mix(color, color0, color0.a);
	vec4 color1 = texture(texture1, vec2(textureCoords.x, textureCoords.y - timeOffset));
	float alpha = color1.a;
	color1.a = 1.0;
	out_color = mix(out_color, color1, alpha);

	// Lights
	bool blinn = true;
	vec3 diffuseSum = vec3(0.0);
	vec3 specularSum = vec3(0.0);

	calculateLight(light0Position, light0Color, diffuseSum, specularSum, blinn);
	calculateLight(light1Position, light1Color, diffuseSum, specularSum, blinn);

	//Fix alpha
	// max for nice shiny specular reflections
	out_color.rgb = out_color.rgb * (diffuseSum + materialAmbient) + max(out_color.rgb, 0.05) * specularSum;
}