#ifndef GAME_BLOCKREGISTRY_H
#define GAME_BLOCKREGISTRY_H

#include <map>
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
    /**
     * Registers all renderers for each block.
     * Can only be called once and must be after all blocks have been registered.
     */
    //unsigned int RegisterBlockRenderer(Block*);
    unsigned int RegisterBlockRenderers();

private:
    // singleton
    BlockRegistry(void);
    BlockRegistry(BlockRegistry const&); // prevent copies
    void operator=(BlockRegistry const&); // prevent assignments
    ~BlockRegistry();

    bool registered_renderers_ = false;
    std::map<unsigned int, Block*> blocks_;

};

#endif //GAME_BLOCKREGISTRY_H
