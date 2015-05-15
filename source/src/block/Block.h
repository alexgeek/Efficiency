#ifndef GAME_BLOCK_H
#define GAME_BLOCK_H

#include <string>
#include "BlockRegistry.h"

class Block {
friend class BlockRegistry;
public:
    Block();
    ~Block();
private:
    unsigned int id_;
};

#endif //GAME_BLOCK_H
