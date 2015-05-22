#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H

#include <string>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "BlockRegistry.h"

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
    Block();
    ~Block();
private:
    unsigned int id_;
};

#endif //GAME_BLOCK_H
