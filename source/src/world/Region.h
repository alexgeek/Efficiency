#ifndef REGION_H
#define REGION_H

#include <iostream>
#include <unordered_map>
#include <gtest/gtest_prod.h>

/**
 * Dimensions are divided into Regions.
 * Regions handle the saving and loading of an area in a Dimension.
 * Regions contain basic blocks, logic blocks, and entities.
 */
class Region
{
    public:
      const static int kBitX = 4;
      const static int kBitY = 8;
      const static int kBitZ = 4;
      const static int kSizeX = 16; // 2^4 = 16
      const static int kSizeY = 256; // 2^8 = 256
      const static int kSizeZ = 16; // 2^4 = 16

      Region(int x, int z);
      int x() const { return x_; }
      int z() const { return z_; }

      void Update();

      /**
       * Get the block that contains in local region coordinates x,y,z.
       *
       * @param x coordinate (local region)
       * @param y coordinate (local region)
       * @param z coordinate (local region)
       * @return block id
       */
      int GetBlock(unsigned char x, unsigned char y, unsigned char z);

      /**
       * Set the block that contains in local region coordinates x,y,z.
       *
       * @param x coordinate (local region)
       * @param y coordinate (local region)
       * @param z coordinate (local region)
       * @param block id to set
       * @return 1 if successful
       */
      int SetBlock(unsigned char x, unsigned char y, unsigned char z, int block);

      /**
       * Set the block in local region coordinates x,y,z to air.
       * It is better to delete the current block from the map than insert 0.
       *
       * @param x coordinate (local region)
       * @param y coordinate (local region)
       * @param z coordinate (local region)
       * @return 1 if successful
       */
      int ClearBlock(unsigned char x, unsigned char y, unsigned char z);
    protected:
    private:
      int x_;
      int z_;
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
      FRIEND_TEST(RegionTest, RegionCollisionCheck);
};

#endif
