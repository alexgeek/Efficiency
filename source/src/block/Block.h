#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BlockRegistry.h"
#include "../render/BatchedRenderCube.h"

class Block;

typedef struct {
    union {
        struct {
            int x, y, z;
        } axis;
        glm::ivec3 vector;
    } position;
    Block* block;
} BlockPosition;

enum CompassDirection {
    UP=0,
    DOWN,
    NORTH,
    SOUTH,
    EAST,
    WEST
};

enum AxisDirection {
    POSITIVEY=0,
    NEGATIVEY,
    POSITIVEX,
    NEGATIVEX,
    POSITIVEZ,
    NEGATIVEZ
};

CompassDirection axis_to_compass(AxisDirection axisDirection);
AxisDirection compass_to_axis(CompassDirection compassDirection);


class Block {
friend class BlockRegistry;
public:
    Block(std::string);
    ~Block();

    std::string GetName() const { return name_; }
    BatchedRenderCube* GetRenderer() const { return renderer_; }
    Block* SetRenderer(BatchedRenderCube* renderer) { renderer_ = renderer; return this; }
private:
    unsigned int id_;
    std::string name_;
    BatchedRenderCube* renderer_;
};

#endif //GAME_BLOCK_H
