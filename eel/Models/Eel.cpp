#include "Eel.h"

Eel::Eel() : RenderModel() {}
Eel::~Eel() {}

void Eel::create(GLfloat length, GLfloat radius, GLuint sectors, const glm::vec4& color) {
	this->length = length;
	this->radius = radius;
	this->sectors = sectors;
	this->color = glm::vec4(color);

	this->construct(0.0f, true);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(VertexFormat), &vertices[0], GL_DYNAMIC_DRAW);

	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

	setAttribPointers();

	// Finish
	this->vao = vao;	
	this->vbos.push_back(vbo);
	this->vbos.push_back(ibo);
}

void Eel::construct(const float time, bool init) {
	vertices.clear();

	const double recip = 1.0 / (double) (sectors - 1);
	const double recipPI = M_PI / (double) sectors;
	const double recip2PI = 2.0 * M_PI * recip;
	const double halfLength = length * 0.5;
	double offsetZ = 0.0f;
	const unsigned int halfSectors = sectors / 2;

	// Head
	for(unsigned int i = 0; i <= halfSectors; i++) {
		const double x = glm::sin(-M_PI / 2 + recipPI * i) * radius * 3;
		double normalX = 0.0f;
		if(animated) {
			double movementFactor = MOVEMENT_SPEED * (double) time + (x - halfLength) * MOVEMENT_LENGTH;
			offsetZ = glm::sin(movementFactor) * MOVEMENT_AMOUNT;
			// -f'(x)
			normalX = -glm::cos(movementFactor) * MOVEMENT_AMOUNT * MOVEMENT_LENGTH;
		}

		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j) * sin(M_PI * i * recip);
			const double z = sin(recip2PI * j) * sin(M_PI * i * recip);

			glm::vec3 pos((float) (x - halfLength), (float) (y * radius), (float) (z * radius + offsetZ));
			glm::vec3 norm((float) x/9.0 + normalX * radius, (float) (y * radius), (float) (z * radius));
			glm::vec2 tex((float) (j * recip), (float) (1.0 + x/length));
			vertices.push_back(VertexFormat(pos, norm, tex, color));
		}
	}
	const unsigned int headVertexCount = vertices.size();
	if(init) {
		// Head faces' indices
		for(unsigned int i = 0; i < halfSectors; i++) {
			for(unsigned int j = 0; j < sectors-1; j++) {
				indices.push_back(i * sectors + j);
				indices.push_back((i + 1) * sectors + j + 1);
				indices.push_back(i * sectors + j + 1);
				indices.push_back(i * sectors + j);
				indices.push_back((i + 1) * sectors + j);
				indices.push_back((i + 1) * sectors + j + 1);
			}
		}
	}
	
	// Body
	const double sectorLength = (double) length / (double) sectors;
	for(unsigned int i = 0; i <= sectors; i++) {
		const double x = (double) i * sectorLength - halfLength;

		double normalX = 0.0f;
		if(animated) {
			double movementFactor = MOVEMENT_SPEED * (double) time + x * MOVEMENT_LENGTH;
			offsetZ = glm::sin(movementFactor) * MOVEMENT_AMOUNT;
			// - f'(x)
			normalX = -glm::cos(movementFactor) * MOVEMENT_AMOUNT * MOVEMENT_LENGTH;
		}

		// Fin front
		glm::vec3 finPos((float) x, 1.8f * radius, (float) offsetZ);
		glm::vec2 finTex((float) (1.0f + 0.4f / M_PI), (float) (recip * i));
		glm::vec3 finNorm(normalX, 0.0f, 1.0f);
		// Front top
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
		finPos.y = radius;
		finTex.x = 1.0f;
		// Front bottom
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));

		// Rest of segment
		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j);
			const double z = sin(recip2PI * j);

			glm::vec3 pos((float) x, (float) (y * radius), (float) (z * radius + offsetZ));
			glm::vec3 norm(normalX, (float) y, (float) (z));
			glm::vec2 tex((float) (j * recip), (float) (i * recip));
			vertices.push_back(VertexFormat(pos, norm, tex, color));
		}

		// Fin back
		finNorm.z = -1.0f;
		// Back bottom
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
		finPos.y = 1.8f * radius;
		finTex.x -= (float)(0.4f / M_PI);
		// Back top
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
	}
	const unsigned int bodyVertexCount = vertices.size();
	if(init) {
		// +2 for fin
		unsigned int sectorsPlus = sectors + 4;
		// Head-body connection
		const unsigned int headLastRing = headVertexCount - sectors;
		for(unsigned int j = 0; j < sectors-1; j++) {
			indices.push_back(headLastRing + j);
			indices.push_back(headLastRing + sectors + j + 3);
			indices.push_back(headLastRing + sectors + j + 3);
			indices.push_back(headLastRing + j);
			indices.push_back(headLastRing + sectors + j + 3);
			indices.push_back(headLastRing + j);
		}

		// Body
		for(unsigned int i = 0; i < sectors; i++) {
			for(unsigned int j = 0; j < sectorsPlus - 1; j++) {
				indices.push_back(headVertexCount + i * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j + 1);
				indices.push_back(headVertexCount + i * sectorsPlus + j + 1);
				indices.push_back(headVertexCount + i * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j + 1);
			}
		}
	}

	// Tail
	const double tailRadiusDiff = (double) radius / (double) halfSectors;
	const double tailSectorLength = 4.0 * tailRadiusDiff;
	for(unsigned int i = 0; i <= halfSectors; i++) {
		const double x = halfLength + i * tailSectorLength;

		double normalX = 0.0f;
		if(animated) {
			double movementFactor = MOVEMENT_SPEED * (double) time + x * MOVEMENT_LENGTH;
			offsetZ = glm::sin(movementFactor) * MOVEMENT_AMOUNT;
			normalX = -glm::cos(movementFactor) * MOVEMENT_AMOUNT * MOVEMENT_LENGTH;
		}

		const double sectionRadius = (halfSectors - i) * tailRadiusDiff;

		// Fin front
		glm::vec3 finPos((float) x, sectionRadius + radius * 0.8, (float) offsetZ);
		glm::vec2 finTex((float) (1.0f + 0.4f / M_PI), (float) (recip * i));
		glm::vec3 finNorm(normalX, 0.0f, 1.0f);
		// Top
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
		finPos.y = (float) sectionRadius;
		finTex.x = 1.0f;
		// Bottom
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));

		// Rest of segment
		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j);
			const double z = sin(recip2PI * j);

			glm::vec3 pos((float) (x), (float) (y * sectionRadius), (float) (z * sectionRadius + offsetZ));
			glm::vec3 norm(normalX, (float) y * radius, (float) z * radius);
			glm::vec2 tex((float) (j * recip), (float) (1.0 + i * recip));
			vertices.push_back(VertexFormat(pos, norm, tex, color));
		}

		// Fin back
		finNorm.z = -1.0f;
		// Bottom
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
		finPos.y = (float)(sectionRadius + radius * 0.8);
		finTex.x -= (float)(0.4f / M_PI);
		// Top
		vertices.push_back(VertexFormat(finPos, finNorm, finTex, color));
	}
	if(init) {
		// +4 for fin
		unsigned int sectorsPlus = sectors + 4;
		// Body-tail connection
		const unsigned int bodyLastRing = bodyVertexCount - sectorsPlus;
		for(unsigned int j = 0; j < sectorsPlus; j++) {
			indices.push_back(bodyLastRing + j);
			indices.push_back(bodyLastRing + sectorsPlus + j);
			indices.push_back(bodyLastRing + sectorsPlus + j + 1);
			indices.push_back(bodyLastRing + j);
			indices.push_back(bodyLastRing + sectorsPlus + j + 1);
			indices.push_back(bodyLastRing + j + 1);
		}

		// Tail
		for(unsigned int i = 0; i < halfSectors; i++) {
			for(unsigned int j = 0; j < sectorsPlus - 1; j++) {
				indices.push_back(bodyVertexCount + i * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j + 1);
				indices.push_back(bodyVertexCount + i * sectorsPlus + j + 1);
				indices.push_back(bodyVertexCount + i * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j + 1);
			}
		}
	}

	if(!init) {
		// Rebind VBO
		glBindBuffer(GL_ARRAY_BUFFER, this->vbos.front());
		// Update VBO data
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexFormat), &vertices[0]);
	}
}

void Eel::update(const float totalTimePassed, const float deltaTime, const bool force) {
	if(!animated && !force) {
		return;
	}
	construct(totalTimePassed);
}

void Eel::draw(const GLuint program) {
	glBindVertexArray(vao);

	setPositionUniforms(program);
	setMaterialUniforms(program);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
