#ifndef GAME_BLOCKREGISTRY_H
#define GAME_BLOCKREGISTRY_H

#include <map>
#include "Block.h"

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

private:
    // singleton
    BlockRegistry(void);
    BlockRegistry(BlockRegistry const&); // prevent copies
    void operator=(BlockRegistry const&); // prevent assignments
    ~BlockRegistry() {};

    std::map<unsigned int, Block*> blocks_;

};

#endif //GAME_BLOCKREGISTRY_H
