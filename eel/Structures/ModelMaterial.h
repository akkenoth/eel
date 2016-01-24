#ifndef _STRUCTURES_MODELMATERIAL_H
#define _STRUCTURES_MODELMATERIAL_H

struct ModelMaterial {
	unsigned int texture;
	float ambient;
	float diffusive;
	float specular;
	float shininess;
	float speedX;
	float speedY;

	ModelMaterial(unsigned int t, float a, float d, float sp, float sh, float sX = 0.0f, float sY = 0.0f) {
		texture = t;
		ambient = a;
		diffusive = d;
		specular = sp;
		shininess = sh;
		speedX = sX;
		speedY = sY;
	}
};

#endif // !_STRUCTURES_MODELMATERIAL_H
