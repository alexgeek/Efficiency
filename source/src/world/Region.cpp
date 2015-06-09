#include "Region.h"
#include "../block/BlockRegistry.h"

Region::Region(int x, int z) :
        x_(x),
        z_(z)
{
}

void Region::Update() {
    for (int x = 0; x < Region::kSizeX; x++) {
        for (int y = 0; y < Region::kSizeY; y++) {
            for (int z = 0; z < Region::kSizeZ; z++) {
                int blockID = this->GetBlock(x, y, z);
                if (blockID > 0) {
                    BatchedRenderCube* render = BlockRegistry::Instance().GetBlock(blockID)->GetRenderer();
                    assert(render != NULL);
                    float blockX = this->x()*16 + x;
                    float blockY = y;
                    float blockZ = this->z()*16 + z;
                    render->BufferPosition(blockX, blockY, blockZ);
                }
            }
        }
    }
}

int Region::GetBlock(unsigned char x, unsigned char y, unsigned char z) {
    const unsigned long int block_key = hash_block_key(x, y, z);
    // if the block does not exist then return air (0)
    if (block_map_.find(block_key) == block_map_.end())
        return 0;
    else
        return block_map_[block_key];
}

int Region::SetBlock(unsigned char x, unsigned char y, unsigned char z, int block) {
    block_map_[hash_block_key(x, y, z)] = block;
    return true;
}

int Region::ClearBlock(unsigned char x, unsigned char y, unsigned char z) {
    block_map_.erase(hash_block_key(x, y, z));
    return true;
}

/**
 * Hashes x,y,z into a 16-bit key.
 * Bitshifts the coordinates such that:
 * [x << 12] [y << 8] [z     ]
 * [4 bits ] [8 bits] [4 bits]
 */
unsigned int Region::hash_block_key(unsigned char x, unsigned char y, unsigned char z) {
    /*return ((x) << 12) & 0xF000 |
           ((y) << 8)  & 0x0FF0 |
             z         & 0x000F;*/
    return ((x) << 24)  & 0xFF000000 |
           ((y) << 16)  & 0x00FFFF00 |
           z            & 0x000000FF;

    //return ((unsigned int) (x << (kBitX + kBitY)) |  (((unsigned int)y)&255 << kBitY) | (unsigned int) (z & 15));
    //return ((unsigned int) (x*31 << (kBitX + kBitY)) | (unsigned int) (y*31 << kBitY) | (unsigned int) (z*31)) % 65536;
}
