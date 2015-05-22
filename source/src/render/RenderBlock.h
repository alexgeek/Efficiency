#ifndef GAME_RENDERBLOCK_H
#define GAME_RENDERBLOCK_H

struct RenderBlockData {
    unsigned int texture_positive_x, texture_positive_y, texture_positive_z;
    unsigned int texture_negative_x, texture_negative_y, texture_negative_z;
    float position_x, position_y, position_z;
}; union {
    glm::uvec3 texture_positive;
    glm::uvec3 texture_negative;
    glm::vec3 position;
} GLMRenderBlockData;


class RenderBlock
{
public:
    RenderBlock();
    ~RenderBlock();

    void RenderBlockAt(BlockPosition blockPosition);

private:
    std::vector<RenderBlockData> render_block_data_;
};

#endif //GAME_RENDERBLOCK_H
