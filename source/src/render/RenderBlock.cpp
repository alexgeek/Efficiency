#include "RenderBlock.h"
#include "../block/Block.h"

void RenderBlock::RenderBlockAt(BlockPosition blockPosition) {
    GLMRenderBlockData renderBlockData;
    renderBlockData.position = (GLMBlockPosition).position;
    const Block* block = blockPosition.block;
    renderBlockData.texture_positive = glm::uvec3(block);
}
