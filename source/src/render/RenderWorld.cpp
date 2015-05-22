#include "RenderWorld.h"

RenderWorld::RenderWorld()
{}

RenderWorld::~RenderWorld()
{}

int RenderWorld::Init() {
    // set up block renderers
    // set up character renderers
    // set up UI
}

BatchedRenderCube* RenderWorld::GetBlockRender(unsigned int blockID) {
    return block_render_[blockID];
}

void RenderWorld::RenderBlock(glm::ivec3 position, unsigned int blockID) {
    GetBlockRender(blockID)->buffer_position(glm::vec3(position));
}

void RenderWorld::RenderBlock(int x, int y, int z, unsigned int blockID) {
    RenderBlock(glm::ivec3(x, y, z), blockID);
}

void RenderWorld::Render(Camera* camera) {
    for(std::map<unsigned int, BatchedRenderCube*>::iterator it = block_render_.begin(); it != block_render_.end(); ++it)
        it->second->render(camera);
}
