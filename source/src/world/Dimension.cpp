#include "Dimension.h"

void Dimension::Update() {
  // TODO update active regions
  for(std::unordered_map<unsigned int, Region*>::iterator it = region_map_.begin(); it != region_map_.end(); it++)
    it->second->Update();
}

int Dimension::LoadRegion(int x, int z) {
  // TODO
  // 1. if loaded return
  // 2. if not loaded then
  //  a. if not generated, generate
  //  b. if generated but not loaded, load
  if(IsRegionLoaded(x, z))
    return 1;
  Region* region = new Region(x, z);
  const unsigned int region_key = hash_region_key(x, z);
  region_map_[region_key] = region;
  return 1;
}

int Dimension::UnloadRegion(int x, int z) {
  // TODO save to file
  const unsigned int region_key = hash_region_key(x, z);
  delete region_map_[region_key];
  region_map_.erase(region_key);
  return 0;
}

Region* Dimension::GetRegion(int x, int z) {
  const unsigned int region_key = hash_region_key(x, z);
  if(region_map_.count(hash_region_key(x, z)) == 0)
    LoadRegion(x, z);
  return region_map_[region_key];
}

std::vector<Region*> Dimension::GetRegionsAroundPrealloc(int x, int z, int distance) {
  std::vector<Region*> regions;
  const int sqrt_size = 2*distance+1;
  regions.reserve(sqrt_size*sqrt_size);
  for(int rx = -distance; rx <= distance; rx++)
    for(int rz = -distance; rz <= distance; rz++)
      regions.push_back(GetRegion(rx + x, rz + z));
  return regions;
}

std::vector<Region*> Dimension::GetRegionsAround(int x, int z, int distance) {
  std::vector<Region*> regions;
  for(int rx = -distance; rx <= distance; rx++)
    for(int rz = -distance; rz <= distance; rz++)
      regions.push_back(GetRegion(rx + x, rz + z));
  return regions;
}

int Dimension::CountLoadedRegions() {
  return region_map_.size();
}

int Dimension::IsRegionLoaded(int x, int z) {
  return region_map_.count(hash_region_key(x, z)) == 1;
}

bool Dimension::SetBlock(int x, int y, int z, int block) {
  const int regionX = x >> 4;
  const int regionZ = z >> 4;
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
