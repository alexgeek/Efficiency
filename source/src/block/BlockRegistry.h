#ifndef GAME_BLOCKREGISTRY_H
#define GAME_BLOCKREGISTRY_H

#include <map>
#include <unordered_map>
#include "Block.h"

class Block;

class BlockRegistry
{
public:
    // singleton
    static BlockRegistry& Instance()
    {
        static BlockRegistry instance;
        return instance;
    }

    unsigned int RegisterBlock(Block* block);
    Block* GetBlock(unsigned int);
    Block* GetBlock(std::string);
    unsigned int Size();

private:
    // singleton
    BlockRegistry(void);
    BlockRegistry(BlockRegistry const&); // prevent copies
    void operator=(BlockRegistry const&); // prevent assignments
    ~BlockRegistry();

    bool registered_renderers_ = false;
    std::map<unsigned int, Block*> blocks_;
    std::unordered_map<std::string, Block*> block_names_;

};

#endif //GAME_BLOCKREGISTRY_H
