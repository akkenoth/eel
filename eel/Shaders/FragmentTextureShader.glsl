#version 330 core

layout(location = 0) out vec4 out_color; // To framebuffer, color location

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture1alpha;
uniform float timePassed;

in vec2 textureCoords;

void main(void) {
	float timeOffset = timePassed * 0.1;
	vec4 color0 = texture(texture0, vec2(textureCoords.x, textureCoords.y));

	vec4 color1 = texture(texture1, vec2(textureCoords.x, textureCoords.y - timeOffset));
	vec4 color1alpha = texture(texture1alpha, vec2(textureCoords.x, textureCoords.y - timeOffset));

	// Here be dragons!
	out_color = mix(color0, color1, color1alpha.r);
}