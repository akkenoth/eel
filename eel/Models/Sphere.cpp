#include "Sphere.h"

Sphere::Sphere() {}

Sphere::~Sphere() {}

void Sphere::create(GLfloat radius, GLuint rings, GLuint sectors) {
	std::vector<VertexFormat> vertices;
	std::vector<GLuint> indices;

	const double ringsRecip = 1.0 / (double) (rings - 1);
	const double sectorsRecip = 1.0 / (double) (sectors - 1);

	for(unsigned int i = 0; i < rings; i++) {
		const double y = sin(-M_PI / 2 + M_PI * i * ringsRecip) * radius;
		for(unsigned int j = 0; j < sectors; j++) {
			const double x = cos(2 * M_PI * j * sectorsRecip) * sin(M_PI * i * ringsRecip);
			const double z = sin(2 * M_PI * j * sectorsRecip) * sin(M_PI * i * ringsRecip);

			glm::vec3 pos((float) (x * radius), (float) (y), (float) (z * radius));
			glm::vec2 tex((float) (j * sectorsRecip), (float) (i * ringsRecip));
			vertices.push_back(VertexFormat(pos, tex));
		}
	}

	for(unsigned int i = 0; i < rings-1; i++) {
		for(unsigned int j = 0; j < sectors-1; j++) {
			indices.push_back(i * sectors + j);
			indices.push_back(i * sectors + j + 1);
			indices.push_back((i + 1) * sectors + j + 1);
			indices.push_back(i * sectors + j);
			indices.push_back((i + 1) * sectors + j + 1);
			indices.push_back((i + 1) * sectors + j);
		}
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_STATIC_DRAW);
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	setAttribPointers();

	// Finish
	this->vao = vao;
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
	indicesCount = indices.size();

	rotationSpeed = glm::vec3(0.0, 30.0, 0.0);
	baseRotation = glm::vec3(30.0, 0.0, 0.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);
	spawnTime = std::chrono::steady_clock::now();
}

void Sphere::update() {
	std::chrono::duration<float> duration = spawnTime - std::chrono::steady_clock::now();
	timePassed = duration.count();
	rotation = timePassed * rotationSpeed + baseRotation;
	rotationSin = glm::vec3(rotation.x * M_PI / 180, rotation.y * M_PI / 180, rotation.z * M_PI / 180);
}

void Sphere::draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix, const glm::mat4& worldMatrix) {
	glUseProgram(program);
	glBindVertexArray(vao);

	// Activate, bind and transform texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->getTexture("sphereTexture0"));
	glUniform1i(glGetUniformLocation(program, "texture0"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, this->getTexture("sphereTexture1"));
	glUniform1i(glGetUniformLocation(program, "texture1"), 1);

	// glActiveTexture(GL_TEXTURE2);
	// glBindTexture(GL_TEXTURE_2D, this->getTexture("sphereTexture1Alpha"));
	// glUniform1i(glGetUniformLocation(program, "texture1alpha"), 2);

	// Apply cube rotation, view and projection transformations
	glUniformMatrix4fv(glGetUniformLocation(program, "worldMatrix"), 1, GL_FALSE, &worldMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, &viewMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, &projectionMatrix[0][0]);
	glUniform3f(glGetUniformLocation(program, "rotation"), rotationSin.x, rotationSin.y, rotationSin.z);
	glUniform1f(glGetUniformLocation(program, "timePassed"), timePassed);
	glUniform3f(glGetUniformLocation(program, "eyePosition"), 0.0f, 0.0f, 3.0f);

	glUniform3f(glGetUniformLocation(program, "light0Position"), 0.0f, 5.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "light0Color"), 5.0f, 5.0f, 5.0f);
	glUniform3f(glGetUniformLocation(program, "light1Position"), 3.0f, 0.0f, 0.0f);
	glUniform3f(glGetUniformLocation(program, "light1Color"), 4.0f, 4.0f, 4.0f);

	glUniform1f(glGetUniformLocation(program, "materialAmbient"), 0.02f);
	glUniform1f(glGetUniformLocation(program, "materialDiffusive"), 0.3f);
	glUniform1f(glGetUniformLocation(program, "materialSpecular"), 0.9f);
	glUniform1f(glGetUniformLocation(program, "materialShininess"), 1.9f);
	glUniform1f(glGetUniformLocation(program, "attenuationConstant"), 1.0f);
	glUniform1f(glGetUniformLocation(program, "attenuationLinear"), 0.0f);
	glUniform1f(glGetUniformLocation(program, "attenuationQuadratic"), 0.0f);
	// glUniform1f(glGetUniformLocation(program, ""), );

	// Draw
	glCullFace(GL_BACK);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
	glCullFace(GL_FRONT);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}
