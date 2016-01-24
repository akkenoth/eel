#version 330 core
// Blinn-Phong shading with attenuation, soft cut-off for specular light and using energy conserving model

const float PI = 3.14159265;
const int MAX_LIGHTS = 4;
const int MAX_MATERIALS = 4;
const bool blinn = true;

// Unused
struct Light {
	vec3 position;
	vec3 color;
	float attenuationConstant;
	float attenuationLinear;
	float attenuationQuadratic;
};

layout(location = 0) out vec4 out_color; // To framebuffer, color location

// From scene manager
// Globals
uniform float timePassed;
uniform vec3 eyePosition;
// Lights
//MAX_LIGHTS
uniform mat3 lights[4];
uniform bool lightIsPointlight[4];
uniform int lightCount;

// Materials (from model)
// Properties: ambient, diffusive, specular, shininess
//MAX_MATERIALS
uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform vec4 materialProperties[4];
uniform vec2 materialSpeeds[4];
uniform int materialCount;

// Vertex properties, from Vertex shader, preserve names!
in vec3 worldPosition;
in vec3 worldNormal;
in vec2 textureCoords;
in vec4 color;

sampler2D getTexture(in int index) {
	// MAX_MATERIALS
	switch(index) {
		case 0:
			return texture0;
		case 1:
			return texture1;
		case 2:
			return texture2;
		case 3:
			return texture3;
	}
}

void calculateMaterial(in sampler2D texturePtr, in vec4 matProps, in vec2 matSpeeds, inout vec4 baseColor, inout vec4 baseProperties) {
	vec2 texturePosition = matSpeeds * timePassed + textureCoords;
	vec4 textureColor = texture(texturePtr, texturePosition);
	float textureAlpha = textureColor.a;
	textureColor.a = 1.0;

	baseColor = mix(baseColor, textureColor, textureAlpha);
	baseProperties = mix(baseProperties, matProps, textureAlpha);
}

void calculateLight(in mat3 light, in bool isPointLight, in float shininess, inout vec3 diffuseSum, inout vec3 specularSum) {
	vec3 lPos = light[0];
	vec3 lColor = light[1];
	float attCons = light[2].x;
	float attLin = light[2].y;
	float attQuad = light[2].z;
	vec3 normal = normalize(worldNormal);

	// Direction TO viewer and light
	vec3 lightDirection;
	if(isPointLight) {
		// Point light - direction to light source is direction to light source position
		lightDirection = normalize(lPos - worldPosition);
	} else {
		// Global illumination - direction to light source is reverse light emission direction
		lightDirection = -lPos;
	}
	float lambertian = dot(normal, lightDirection);
	// We're interested in this light source only if angle <= +-90deg
	float d = distance(lPos, worldPosition);
	float att = 1.0 / (attCons + d * attLin + d * d * attQuad);
		
	if(lambertian > 0.0) {
		diffuseSum += att * lColor * lambertian;
	}

	vec3 reflectDir;
	float energyCoeff = 0.0;
	if(blinn) {
		// Blinn-Phong
		energyCoeff = (8.0 + shininess) / (8.0 * PI);
		// halfway between direction to light and to viewer
		vec3 viewDirection = normalize(eyePosition - worldPosition);
		reflectDir = normalize(lightDirection + viewDirection);
	} else {
		// Phong
		energyCoeff = (2.0 + shininess) / (2.0 * PI);
		// Straight reflection
		reflectDir = reflect(-lightDirection, normal);
	}
	float angle = dot(normal, reflectDir);
	if(angle > 0.0) {
		specularSum += lColor * att * energyCoeff * pow(angle, shininess * 4.0);
	}
}

void main(void) {
	// Base color and material properties
	vec4 baseColor = color;
	vec4 baseProperties = materialProperties[0];

	// Materials
	for(int i = 0; i < materialCount; i++) {
		calculateMaterial(getTexture(i), materialProperties[i], materialSpeeds[i], baseColor, baseProperties);
	}
	
	float ambient = baseProperties.x;
	float diffusive = baseProperties.y;
	float specular = baseProperties.z;
	float shininess = baseProperties.w;

	// Lights
	vec3 diffuseSum = vec3(0.0);
	vec3 specularSum = vec3(0.0);
	for(int i = 0; i < lightCount; i++) {
		calculateLight(lights[i], lightIsPointlight[i], shininess, diffuseSum, specularSum);
	}

	out_color = baseColor;
	out_color.rgb *= (diffuseSum * diffusive + vec3(ambient));
	out_color.rgb += specularSum * baseColor.a * specular;
}