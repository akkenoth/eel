#ifndef _MODELS_RENDERMODEL_H
#define _MODELS_RENDERMODEL_H

#include "../Interfaces/RenderObject.h"
#include "../Structures/ModelMaterial.h"
#include "../Libs/glm/gtc/type_ptr.hpp"
#include "../Libs/glm/gtc/matrix_transform.hpp"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif // !M_PI

#define MAX_MATERIALS 4

class RenderModel : public RenderObject {
protected:
	GLuint vao;
	std::vector<GLuint> vbos;
	ModelMaterial* baseMaterial;
	std::vector<ModelMaterial*> materials;
	GLuint normalMap;
	glm::vec3 worldPosition;
	glm::vec3 rotation;
	glm::vec3 rotationSpeed;
	bool animated;

	virtual void setAttribPointers() const;
	virtual void rotate(float deltaTime);
	virtual void setPositionUniforms(const GLuint program) const;
	virtual void setMaterialUniforms(const GLuint program) const;
public:
	RenderModel();
	virtual ~RenderModel();

	virtual void draw() override;
	virtual void draw(const GLuint program) override;
	virtual void update(const float totalTimePassed = 0.0f, const float deltaTime = 0.0f, const bool force = false) override;
	virtual void destroy() override;

	virtual void setPosition(const glm::vec3& newPosition);
	virtual void setRotation(const glm::vec3& newRotation);
	virtual void setRotationSpeed(const glm::vec3& newRotationSpeed);

	virtual void toggleAnimation(const float totalTimePassed);

	virtual void setBaseMaterial(float ambient, float diffusive, float specular, float shininess);
	virtual void addMaterial(unsigned int index, const std::string& textureFileName, float ambient, float diffusive, float specular, float shininess, TextureLoader* textureLoader);
	virtual void clearMaterial(unsigned int index);

	virtual void addNormalMap(const std::string& textureFileName, TextureLoader* textureLoader);
	virtual void clearNormalMap();

	virtual GLuint getVao() const override;
	virtual const std::vector<GLuint>& getVbos() const override;
};

#endif // !_MODELS_RENDERMODEL_H
