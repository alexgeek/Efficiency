#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <unordered_map>

/**
 * Dimensions are divided into Regions.cma
 * Regions handle the saving and loading of an area in a Dimension.
 * Regions contain basic blocks, logic blocks, and entities.
 */
class Region
{
    public:
      const static int kBitX = 4;
      const static int kBitY = 8;
      const static int kBitZ = 4;
      const static int kSizeX = 2^kBitX; // 2^4 = 16
      const static int kSizeY = 2^kBitY; // 2^8 = 256
      const static int kSizeZ = 2^kBitZ; // 2^4 = 16
      /**
       * Get the block that contains in dimension coordinates x,y,z.
       *
       * @param x coordinate (world)
       * @param x coordinate (world)
       * @param x coordinate (world)
       * @return 0 for air, -1 for logic block, 1+ standard blocks
       */
      int GetBlock(unsigned char x, unsigned char y, unsigned char z);
      bool SetBlock(unsigned char x, unsigned char y, unsigned char z, int block);
      bool ClearBlock(unsigned char x, unsigned char y, unsigned char z);
    protected:
    private:
      std::unordered_map<unsigned int, int> block_map_;
      /**
       * Hash local region coordinates as an index to block_map_.
       *
       * @param x coordinate (region) [0-15]
       * @param y coordinate (region) [0-255]
       * @param z coordinate (region) [0-15]
       * @return 16 bit hash of x,y,z
       */
      unsigned int hash_block_key(unsigned char x, unsigned char y, unsigned char z);
};

#endif
