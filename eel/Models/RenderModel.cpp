#include "RenderModel.h"

RenderModel::RenderModel() {
	for(ModelMaterial* mat : materials) {
		mat = NULL;
	}
	normalMap = 0;

	worldPosition = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
	rotation = glm::vec3(0.0f);
}

RenderModel::~RenderModel() {
	destroy();
}

void RenderModel::draw() {}

void RenderModel::draw(const GLuint program) {}

void RenderModel::update(const float totalTimePassed, const float deltaTime) {}

void RenderModel::destroy() {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
	for(ModelMaterial* mat : materials) {
		delete mat;
	}
}

void RenderModel::setPosition(const glm::vec3& newPosition) {
	worldPosition = glm::vec3(newPosition);
}

void RenderModel::setRotation(const glm::vec3& newRotation) {
	rotation = newRotation * (float)(M_PI) / 180.0f;
}

void RenderModel::setRotationSpeed(const glm::vec3& newRotationSpeed) {
	rotationSpeed = newRotationSpeed * (float)(M_PI) / 180.0f;
}

void RenderModel::rotate(float deltaTime) {
	rotation += deltaTime * rotationSpeed;
	if(rotation.x >= 2.0 * M_PI) {
		rotation.x = 0.0f;
	}
	if(rotation.y >= 2.0 * M_PI) {
		rotation.y = 0.0f;
	}
	if(rotation.z >= 2.0 * M_PI) {
		rotation.z = 0.0f;
	}
}

void RenderModel::setPositionUniforms(const GLuint program) const {
	glm::mat4 modelPosition = glm::mat4(1.0f);
	modelPosition[0][3] = worldPosition.x;
	modelPosition[1][3] = worldPosition.y;
	modelPosition[2][3] = worldPosition.z;

	glUniformMatrix4fv(glGetUniformLocation(program, "modelPosition"), 1, GL_FALSE, &modelPosition[0][0]);
	glUniform3f(glGetUniformLocation(program, "rotation"), rotation.x, rotation.y, rotation.z);
}

void RenderModel::setAttribPointers() const {
	// Vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::position)));
	// Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::normal)));
	// Color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	// Texture
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::texture)));

	glBindVertexArray(0);
}

void RenderModel::addMaterial(unsigned int index, const std::string& textureFileName, float ambient, float diffusive, float specular, float shininess, TextureLoader* textureLoader) {
	// Reject if trying to put after empty "slots" or if maximum reached
	if(index > materials.size() || materials.size() >= MAX_MATERIALS) {
		return;
	}

	GLuint texture = textureLoader->loadTexture(textureFileName);
	if(texture == 0) {
		return;
	}

	ModelMaterial* material = new ModelMaterial(texture, ambient, diffusive, specular, shininess);
	materials.insert(materials.begin() + index, material);
}

GLuint getTextureConst(int i) {
	switch(i) {
		case 0:
			return GL_TEXTURE0;
		case 1:
			return GL_TEXTURE1;
		case 2:
			return GL_TEXTURE2;
		case 3:
			return GL_TEXTURE3;
		case 4:
			return GL_TEXTURE4;
		case 5:
			return GL_TEXTURE5;
		case 6:
			return GL_TEXTURE6;
		case 7:
			return GL_TEXTURE7;
		case 8:
			return GL_TEXTURE8;
		default:
			return -1;
	}
}

void RenderModel::setMaterialUniforms(const GLuint program) const {
	// Send texture and create texture property vectors
	std::vector<int> textureIndices;
	std::vector<glm::vec4> properties;
	properties.reserve(MAX_MATERIALS);
	std::vector<glm::vec2> speeds;
	speeds.reserve(MAX_MATERIALS);
	int i = 0;
	for(auto const& mat : materials) {
		if(mat == NULL) {
			continue;
		}

		GLuint tex = getTextureConst(i);
		if(tex == -1) {
			continue;
		}

		glActiveTexture(tex);
		glBindTexture(GL_TEXTURE_2D, mat->texture);
		std::string textureUniformString = std::string("texture") + std::to_string(i);
		glUniform1i(glGetUniformLocation(program, textureUniformString.c_str()), i);

		textureIndices.push_back(i);
		properties.push_back(glm::vec4(mat->ambient, mat->diffusive, mat->specular, mat->shininess));
		speeds.push_back(glm::vec2(mat->speedX, mat->speedY));
		++i;
	}
	
	// Now magical glm/vector pointer hacks begin, just ensure sizes
	static_assert(sizeof(glm::vec4) == sizeof(GLfloat) * 4, "Platform doesn't support this directly.");
	static_assert(sizeof(glm::vec2) == sizeof(GLfloat) * 2, "Platform doesn't support this directly.");

	glUniform4fv(glGetUniformLocation(program, "materialProperties"), MAX_MATERIALS, glm::value_ptr(properties[0]));
	glUniform2fv(glGetUniformLocation(program, "materialSpeeds"), MAX_MATERIALS, glm::value_ptr(speeds[0]));
	glUniform1i(glGetUniformLocation(program, "materialCount"), i);

	// Send normal map (if it exists and we still have free buffers)
	int normalTextureIndex = i + 1;
	GLuint tex = getTextureConst(normalTextureIndex);
	if(normalMap == 0 || tex == -1) {
		glUniform1i(glGetUniformLocation(program, "useNormalMap"), false);
		return;
	}

	glActiveTexture(tex);
	glBindTexture(GL_TEXTURE_2D, normalMap);
	glUniform1i(glGetUniformLocation(program, "useNormalMap"), true);
	glUniform1i(glGetUniformLocation(program, "normalMap"), normalTextureIndex);
}

void RenderModel::clearMaterial(unsigned int index) {
	if(index >= materials.size()) {
		return;
	}
	materials.erase(materials.begin() + index);
}

void RenderModel::addNormalMap(const std::string& textureFileName, TextureLoader* textureLoader) {
	GLuint texture = textureLoader->loadTexture(textureFileName);
	if(texture == 0) {
		return;
	}

	normalMap = texture;
}

void RenderModel::clearNormalMap() {
	normalMap = 0;
}

GLuint RenderModel::getVao() const {
	return vao;
}

const std::vector<GLuint>& RenderModel::getVbos() const {
	return vbos;
}
