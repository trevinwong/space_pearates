#ifndef RENDER_TO_TEXTURE_SYSTEM_H
#define RENDER_TO_TEXTURE_SYSTEM_H

#include "../Utility/utility.hpp"
#include "../Utility/program.hpp"
#include "../Utility/texture.hpp"
#include "../entity_manager.hpp"
#include "../Components/transform_component.hpp"
#include "../Components/TowerComponents/tower_attack_component.hpp"

class RenderToTextureSystem
{
public:
  ~RenderToTextureSystem();

  // initial program, VAO and VBO, and call "prepareWaterEffect"
  bool initWaterEffect();
  // this func is put in the draw. 
  // every render below this func will be render into the water buffer 
  bool beforeRenderWaterEffect();

  // render the water
  void drawWaterEffect(EntityManager entityManager, glm::mat3 projection);

private:
  // this function prepare a blank texture, which is used to be rendered to
  bool prepareWaterEffect();

  // return vec3(towerFirePosX, towerFirePosY, attackRange)
  vector<vec3> getWaterTowerPosAndRange(EntityManager entityManager);

  shared_ptr<Program> waterProgram;

  GLuint depthrenderbuffer = 0;
  GLuint FramebufferName = 0;
  GLuint renderedTexture;
  GLuint VBO;
  GLuint quadVAO;
};
#endif