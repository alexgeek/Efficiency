#include "BlockRegistry.h"

unsigned int BlockRegistry::RegisterBlock(Block *block) {
    static unsigned int uid = 0;
    if(blocks_.insert(std::pair<unsigned int, Block*>(++uid, block)).second)
        return uid;
    else
        return 0;
}

Block* BlockRegistry::GetBlock(unsigned int id) {
    return blocks_[id];
}