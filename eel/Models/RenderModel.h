#ifndef _MODELS_RENDERMODEL_H
#define _MODELS_RENDERMODEL_H

#include <chrono>
#include "../Interfaces/RenderObject.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif // !M_PI

class RenderModel : public RenderObject {
protected:
	GLuint vao;
	GLuint program;
	std::vector<GLuint> vbos;
	std::map<std::string, GLuint> textures;
public:
	RenderModel();
	virtual ~RenderModel();

	virtual void draw() override;
	virtual void draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& worldMatrix) override;
	virtual void update() override;
	virtual void destroy() override;
	virtual void setProgram(GLuint program) override;
	virtual void setTexture(const std::string& textureName, GLuint texture) override;

	virtual GLuint getVao() const override;
	virtual const std::vector<GLuint>& getVbos() const override;
	virtual const GLuint getTexture(const std::string& textureName) const override;
};

#endif // !_MODELS_RENDERMODEL_H
