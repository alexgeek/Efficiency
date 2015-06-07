#include "RenderWorld.h"
#include "../block/BlockRegistry.h"

RenderWorld::RenderWorld() { }

RenderWorld::~RenderWorld() { }

int RenderWorld::Init() {
    this->block_render_ = BlockRegistry::Instance().GetBlockRenderers();
    // set up block renderers
    // set up character renderers
    // set up UI
}

BatchedRenderCube *RenderWorld::GetBlockRender(unsigned int blockID) {
    return block_render_[blockID];
}

void RenderWorld::RenderBlock(glm::ivec3 position, unsigned int blockID) {
    GetBlockRender(blockID)->BufferPosition(glm::vec3(position));
}

void RenderWorld::RenderBlock(int x, int y, int z, unsigned int blockID) {
    RenderBlock(glm::ivec3(x, y, z), blockID);
}

void RenderWorld::ClearBuffers() {
    for (std::map<unsigned int, BatchedRenderCube*>::iterator it = block_render_.begin();
         it != block_render_.end(); ++it)
        it->second->ClearBuffer();
}

void RenderWorld::Render(Camera *camera) {
    for (std::map<unsigned int, BatchedRenderCube*>::iterator it = block_render_.begin();
         it != block_render_.end(); ++it)
        it->second->Render(camera);
}
