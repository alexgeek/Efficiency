#include "BlockRegistry.h"

BlockRegistry::BlockRegistry()
{}

unsigned int BlockRegistry::RegisterBlock(Block *block) {
    static unsigned int uid = 0;
    block->id_ = ++uid; // friend relation
    if(blocks_.insert(std::pair<unsigned int, Block*>(uid, block)).second) {
        block_names_[block->GetName()] = block;
        return uid;
    }
    else
        return 0;
}

Block* BlockRegistry::GetBlock(unsigned int id) {
    return blocks_[id];
}

Block* BlockRegistry::GetBlock(std::string name) {
    return block_names_[name];
}

unsigned int BlockRegistry::Size() {
    return blocks_.size();
}

BlockRegistry::~BlockRegistry() {
    for(std::map<unsigned int, Block*>::iterator it = blocks_.begin(); it != blocks_.end(); it++)
        delete it->second;
}
