#include "sprite_component.hpp"

SpriteComponent::SpriteComponent(Program *_program, Texture *_texture) :
	program(_program), texture(_texture)
{
	// We want to create a square in which we can overlay our texture on.
	GLuint VBO;
	// Define our vertices (a square is composed of two triangles.)
	// We define 6 vertices because we don't want to use IBOs.

	// OpenGL culls backwards faces, so we would typically define our vertices in a counter-clockwise order, as those are considered front-facing.
	// However, our projection matrix is a reflection of the X-axis, so faces get flipped.
	// Hence we define our vertices in clockwise order so that they get flipped to front-facing triangles.
	// TO-DO: Find out why the template can define in counter-clockwise order and not get culled.
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	// Generate a VAO.
	glGenVertexArrays(1, &this->quadVAO);
	// Generate a VBO.
	glGenBuffers(1, &VBO);

	// Bind our current VBO.
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Move the vertices we defined above into our VBO.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Bind our current VAO, which will remember any vertex attribute related calls.
	glBindVertexArray(this->quadVAO);
	// Enable the first "in" variable in our vertex shader - make sure that this corresponds to the right variable!
  // i.e. layout (location = 0) in shaders
  glEnableVertexAttribArray(0);
  //                   (index, size, type, isNormalized, stride, pointer to offset)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
  // layout (location = 1)
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));

	// Re-bind the current VBO and VAO to 0 to avoid accidentally modifying the ones we just configured here.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

SpriteComponent::~SpriteComponent()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

