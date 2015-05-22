#ifndef GAME_RENDERWORLD_H
#define GAME_RENDERWORLD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>         // core window handling
#include <glm/gtc/matrix_transform.hpp> // rotate etc
#include <glm/gtc/type_ptr.hpp> // replace with macro for glm to and from opengl
#include <map>

#include "../camera/Camera.h"
#include "BatchedRenderCube.h"

class RenderWorld
{
public:
    RenderWorld();
    ~RenderWorld();
    int Init();
    BatchedRenderCube* GetBlockRender(unsigned int blockID);
    void RenderBlock(int x, int y, int z, unsigned int blockID);
    void RenderBlock(glm::ivec3 position, unsigned int blockID);
    void Render(Camera* camera);
private:
    std::map<unsigned int, BatchedRenderCube*> block_render_;
};

#endif //GAME_RENDERWORLD_H
