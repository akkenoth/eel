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
		const double x = glm::sin(-M_PI / 2 + recipPI * i) * radius * 2;
		if(animated) {
			offsetZ = glm::sin(MOVEMENT_SPEED * (double) time + x - halfLength) * MOVEMENT_AMOUNT;
		}

		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j) * sin(M_PI * i * recip);
			const double z = sin(recip2PI * j) * sin(M_PI * i * recip);

			glm::vec3 pos((float) (x - halfLength), (float) (y * radius), (float) (z * radius + offsetZ));
			glm::vec2 tex((float) (j * recip), (float) (1.0 - x/length));
			vertices.push_back(VertexFormat(pos, tex, color));
		}
	}
	if(init) {
		// Head indices
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
		if(animated) {
			offsetZ = glm::sin(MOVEMENT_SPEED * (double) time + x) * MOVEMENT_AMOUNT;
		}

		// Fin
		glm::vec3 finPos((float) x, radius * 1.8, (float) offsetZ);
		glm::vec2 finTex((float) (0.4f / M_PI), (float) (recip * i));
		vertices.push_back(VertexFormat(finPos, finTex, color));

		// Rest of segment
		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j);
			const double z = sin(recip2PI * j);

			glm::vec3 pos((float) (x), (float) (y * radius), (float) (z * radius + offsetZ));
			glm::vec2 tex((float) (j * recip), (float) (i * recip));
			vertices.push_back(VertexFormat(pos, tex, color));
		}
	}
	if(init) {
		// Head-body connection
		for(unsigned int j = 1; j < sectors; j++) {
			indices.push_back(halfSectors * sectors + j);
			indices.push_back((halfSectors + 1) * sectors + j + 1);
			indices.push_back(halfSectors * sectors + j + 1);
			indices.push_back(halfSectors * sectors + j);
			indices.push_back((halfSectors + 1) * sectors + j);
			indices.push_back((halfSectors + 1) * sectors + j + 1);
		}

		// Body indices
		unsigned int headVertexCount = sectors * (halfSectors + 1);
		// +1 for fin
		unsigned int sectorsPlus = sectors + 1;
		for(unsigned int i = 0; i < sectors; i++) {
			for(unsigned int j = 0; j < sectors; j++) {
				indices.push_back(headVertexCount + i * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j + 1);
				indices.push_back(headVertexCount + i * sectorsPlus + j + 1);
				indices.push_back(headVertexCount + i * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j);
				indices.push_back(headVertexCount + (i + 1) * sectorsPlus + j + 1);
			}
			// Fin's other side
			indices.push_back(headVertexCount + i * sectorsPlus);
			indices.push_back(headVertexCount + i * sectorsPlus + sectors);
			indices.push_back(headVertexCount + (i + 1) * sectorsPlus + sectors);
			indices.push_back(headVertexCount + i * sectorsPlus);
			indices.push_back(headVertexCount + (i + 1) * sectorsPlus + sectors);
			indices.push_back(headVertexCount + (i + 1) * sectorsPlus);
		}
	}

	// Tail
	const double tailRadiusDiff = (double) radius / (double) halfSectors;
	const double tailSectorLength = 4.0 * tailRadiusDiff;
	for(unsigned int i = 0; i <= halfSectors; i++) {
		const double x = halfLength + i * tailSectorLength;
		if(animated) {
			offsetZ = glm::sin(MOVEMENT_SPEED * (double) time + x) * MOVEMENT_AMOUNT;
		}

		const double sectionRadius = (halfSectors - i) * tailRadiusDiff;

		// Fin
		glm::vec3 finPos((float) x, sectionRadius + radius * 0.8, (float) offsetZ);
		glm::vec2 finTex((float) (0.4f / M_PI), (float) (1.0 + recip * i));
		vertices.push_back(VertexFormat(finPos, finTex, color));

		// Rest of segment
		for(unsigned int j = 0; j < sectors; j++) {
			const double y = cos(recip2PI * j);
			const double z = sin(recip2PI * j);

			glm::vec3 pos((float) (x), (float) (y * sectionRadius), (float) (z * sectionRadius + offsetZ));
			glm::vec2 tex((float) (j * recip), (float) (1.0 + i * recip));
			vertices.push_back(VertexFormat(pos, tex, color));
		}
	}
	if(init) {
		unsigned int sectorsPlus = sectors + 1;
		// Body-tail connection
		unsigned int headVertexCount = sectors * (halfSectors + 1);
		for(unsigned int j = 0; j < sectors; j++) {
			indices.push_back(headVertexCount + sectors * sectorsPlus + j);
			indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus + j + 1);
			indices.push_back(headVertexCount + sectors * sectorsPlus + j + 1);
			indices.push_back(headVertexCount + sectors * sectorsPlus + j);
			indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus + j);
			indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus + j + 1);
		}
		// Fin's other side
		indices.push_back(headVertexCount + sectors * sectorsPlus);
		indices.push_back(headVertexCount + sectors * sectorsPlus + sectors);
		indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus + sectors);
		indices.push_back(headVertexCount + sectors * sectorsPlus);
		indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus + sectors);
		indices.push_back(headVertexCount + (sectors + 1) * sectorsPlus);

		unsigned int bodyVertexCount = headVertexCount + (sectors + 1) * (sectors + 1);
		// +1 for fin
		for(unsigned int i = 0; i < halfSectors; i++) {
			for(unsigned int j = 0; j < sectors; j++) {
				indices.push_back(bodyVertexCount + i * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j + 1);
				indices.push_back(bodyVertexCount + i * sectorsPlus + j + 1);
				indices.push_back(bodyVertexCount + i * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j);
				indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + j + 1);
			}
			// Fin's other side
			indices.push_back(bodyVertexCount + i * sectorsPlus);
			indices.push_back(bodyVertexCount + i * sectorsPlus + sectors);
			indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + sectors);
			indices.push_back(bodyVertexCount + i * sectorsPlus);
			indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus + sectors);
			indices.push_back(bodyVertexCount + (i + 1) * sectorsPlus);
		}
	}
	
	if(!init) {
		std::cout << "vert size" << vertices.size() << "\n";

		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(VertexFormat), &vertices[0]);
	}
}

void Eel::update(const float totalTimePassed, const float deltaTime) {
	if(!animated) {
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
