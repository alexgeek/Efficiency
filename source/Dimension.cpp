#include "Dimension.h"

int Dimension::LoadRegion(int x, int z) {
  // TODO
  // 1. if loaded return
  // 2. if not loaded then
  //  a. if not generated, generate
  //  b. if generated but not loaded, load
  Region* region = new Region();
  //region->SetBlock(0,0,0,1);
  region_map_[hash_region_key(x, z)] = region;

  return 0;
}

int Dimension::UnloadRegion(int x, int z) {
  // TODO save to file
  const unsigned int region_key = hash_region_key(x, z);
  delete region_map_[region_key];
  region_map_.erase(region_key);
  return 0;
}

Region* Dimension::GetRegion(int x, int z) {
  // TODO if the map contains NULL at x,z
  // then load the region
  return region_map_[hash_region_key(x, z)];
}

bool Dimension::SetBlock(int x, int y, int z, int block) {
  const int regionX = x >> 4;//Region::kBitX;
  const int regionZ = z >> 4;//Region::kBitZ;
  Region* region = this->GetRegion(regionX, regionZ);
  return region->SetBlock((unsigned char)x & 15, (unsigned char)y & 15, (unsigned char)z & 15, block);
}

int Dimension::GetBlock(int x, int y, int z) {
  return GetRegion(x >> Region::kBitX, z >> Region::kBitZ)->
    GetBlock((unsigned char)x & 15, (unsigned char)y & 15, (unsigned char)z & 15);
}

bool Dimension::ClearBlock(int x, int y, int z) {
  return GetRegion(x >> Region::kBitX, z >> Region::kBitZ)->
    ClearBlock((unsigned char)x & 15, (unsigned char)y & 15, (unsigned char)z & 15);
}

/**
 * This computes a hash key based on region location (x,z).
 * Uses cantor pairing adjusted to account for negative inputs and outputs.
 *
 * http://en.cppreference.com/w/cpp/container/unordered_map/unordered_map#Example
 * http://stackoverflow.com/questions/919612/mapping-two-integers-to-one-in-a-unique-and-deterministic-way
 *
 * @param x coordinate (region)
*/
unsigned int Dimension::hash_region_key(int x, int z) {
  unsigned int X = (unsigned int)(x >= 0 ? 2 * x : -2 * x - 1);
  unsigned int Z = (unsigned int)(z >= 0 ? 2 * z : -2 * z - 1);
  int H = (int)((X >= Z ? X * X + X + Z : X + Z * Z) / 2);
  return (x < 0 && z < 0) || (x >= 0 && z >= 0) ? H : -H - 1;
}
