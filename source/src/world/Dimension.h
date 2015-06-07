#ifndef DIMENSION_H
#define DIMENSION_H

#include <vector>
#include <unordered_map>
#include <iostream>
#include <assert.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Region.h"

class Dimension
{
    public:
        /* update everything in the dimension */
        void Update();
        int LoadRegion(int x, int z);
        int UnloadRegion(int x, int z);
        Region* GetRegion(int x, int z);
        std::vector<Region*> GetRegionsAround(int x, int z, int distance);
        std::vector<Region *> GetRegionsAroundPrealloc(int x, int z, int distance);
        int CountLoadedRegions();
        int IsRegionLoaded(int x, int z);
        int GetBlock(int x, int y, int z);
        bool SetBlock(int x, int y, int z, int block);
        bool ClearBlock(int x, int y, int z);

        /** accessors & mutators **/
        std::string name() const { return name_; }
        void set_name(std::string name) { name_ = name; }
    protected:
    private:
      std::string name_;
      std::unordered_map<unsigned int, Region*> region_map_;
      unsigned int hash_region_key(int x, int z);
      int LoadRegion(unsigned int key);

};


#endif
