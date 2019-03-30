#include "game_over_menu.hpp"
	
GameOverMenu::GameOverMenu() 
{
    init();
}

GameOverMenu::~GameOverMenu()
{
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}

void GameOverMenu::init() {
    texture = make_shared<Texture>(texture_path("gameover.png"), true); // TODO: FIX
    program = make_shared<Program>(shader_path("sprite.vert"), shader_path("sprite.frag"));

    GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

    // generate VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO); 

    // bind current VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO); 

    // upload vertex data into VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // bind current VAO 
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2*sizeof(GLfloat)));

    glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GameOverMenu::reset() {
    audio_played = false;
}

void GameOverMenu::draw(glm::mat4 projection) {
    
    if(HUD::getInstance().game_over == true) {

        if(!audio_played) {
            Mix_PlayChannel(-1, AudioLoader::getInstance().game_over, 0);
            audio_played = true;
        }
        program->use();
    
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, vec3(vec2(position), 0.0f));
        model = glm::scale(model, vec3(scale, 1.0f));
        

        program->setMat4("model", model);
        program->setMat4("projection", projection);
        program->setVec4("spriteColor", glm::vec4(1.0, 1.0, 1.0, 1.0));
    
        glBindBuffer(GL_ARRAY_BUFFER, VAO);
        
        glActiveTexture(GL_TEXTURE0);

        texture->bind();

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }
    else {
        return;
    }
}

