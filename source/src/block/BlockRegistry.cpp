#include "BlockRegistry.h"

unsigned int BlockRegistry::RegisterBlock(Block *block) {
    static unsigned int uid = 0;
    block->id_ = ++uid; // friend relation
    if(blocks_.insert(std::pair<unsigned int, Block*>(uid, block)).second)
        return uid;
    else
        return 0;
}

Block* BlockRegistry::GetBlock(unsigned int id) {
    return blocks_[id];
}

unsigned int BlockRegistry::RegisterBlockRenderers() {
    /*if(!registered_renderers_) {
        for(std::map<unsigned int, Block*>::iterator it = blocks_.begin(); it != blocks_.end(); it++)
    } else return 0;*/
    return 0; // TODO
}

BlockRegistry::~BlockRegistry() {
    for(std::map<unsigned int, Block*>::iterator it = blocks_.begin(); it != blocks_.end(); it++)
        delete it->second;
}