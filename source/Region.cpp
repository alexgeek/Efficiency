#include "Region.h"

int Region::GetBlock(unsigned char x, unsigned char y, unsigned char z) {
  const unsigned long int block_key = hash_block_key(x,y,z);
  // if the block does not exist then return air (0)
  if(block_map_.find(block_key) == block_map_.end())
    return 0;
  else
    return block_map_[block_key];
}

bool Region::SetBlock(unsigned char x, unsigned char y, unsigned char z, int block) {
  block_map_[hash_block_key(x,y,z)] = block;
  return true;
}

bool Region::ClearBlock(unsigned char x, unsigned char y, unsigned char z) {
  block_map_.erase(hash_block_key(x,y,z));
  return true;
}

unsigned int Region::hash_block_key(unsigned char x, unsigned char y, unsigned char z) {
  return ((unsigned int)(x << (kBitX + kBitY)) | (unsigned int)(y << kBitY) | (unsigned int)(z));
}
