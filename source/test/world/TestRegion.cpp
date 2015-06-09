#ifndef TESTWORLD
#define TESTWORLD

#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include "gtest/gtest.h"
#include "../../src/world/Dimension.h"
#include "../../src/world/Region.h"

class RegionTest : public testing::Test {
protected:
    Dimension* dimension_;

    //  called before each test is run.
    virtual void SetUp() {
        dimension_ = new Dimension();
    }

    // called at the end of each test
    virtual void TearDown() {
        delete dimension_;
    }
};

TEST_F(RegionTest, RegionAccessSquare) {
    const unsigned int size = 3;
    int x, z;
    for(x = -size; x <= size; x++) {
        for (z = -size; z <= size; z++) {
            Region *region = dimension_->GetRegion(x, z);
            EXPECT_EQ(x, region->x());
            EXPECT_EQ(z, region->z());
        }
    }
}

TEST_F(RegionTest, RegionCollisionCheck) {
    std::set<unsigned int> hashes;
    std::unordered_map<unsigned int, unsigned int> collisions;
    Region *region = dimension_->GetRegion(0, 0);

    for (int x = 0; x < Region::kSizeX; x++) {
        for (int y = 0; y < Region::kSizeY; y++) {
            for (int z = 0; z < Region::kSizeZ; z++) {
                const unsigned int hash = region->hash_block_key(x, y, z);
                const bool is_member = hashes.find(hash) != hashes.end();
                if(is_member) {
                    collisions[hash]++;
                } else {
                    hashes.insert(hash);
                }
            }
        }
    }

    unsigned int total_collisions = 0;
    for(std::unordered_map<unsigned int, unsigned int>::iterator it = collisions.begin();
        it != collisions.end(); it++)
    {
        total_collisions += it->second;
    }

    EXPECT_EQ(total_collisions, 0);
    EXPECT_EQ(collisions.size(), 0);
    EXPECT_EQ(hashes.size(), 65536);
}

#endif