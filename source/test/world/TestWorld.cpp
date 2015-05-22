#ifndef TESTWORLD
#define TESTWORLD

#include <iostream>
#include "gtest/gtest.h"
#include "../../src/world/Dimension.h"

class DimensionTest : public testing::Test {
protected:
    Dimension* dimension_;
    // [-size_,size_] range for getting/setting blocks
    const int size_ = 20;
    const int region_line_length_ = 64;
    // for GetChunksAround, chunk distance in each direction
    const int region_distance_ = 16;

    //  called before each test is run.
    virtual void SetUp() {
        dimension_ = new Dimension();
        preallocate_dimension();
    }

    void preallocate_dimension() {
        int x, y, z;
        for(x = -size_; x <= size_; x++)
            for(y = 0; y <= size_; y++)
                for(z = -size_; z <= size_; z++) {
                    const int blockID = get_block_id(x,y,z);
                    dimension_->SetBlock(x, y, z, blockID);
                }
    }

    int get_block_id(int x, int y, int z) {
        return 1;
    }

    // called at the end of each test
    virtual void TearDown() {
        delete dimension_;
    }

};

TEST_F(DimensionTest, RegionAccessSquare) {
    const unsigned int size = 3;
    int x, z;
    for(x = -size; x <= size; x++)
        for(z = -size; z <= size; z++){
            Region* region = dimension_->GetRegion(x,z);
            EXPECT_EQ(x, region->x());
            EXPECT_EQ(z, region->z());
        }
}

TEST_F(DimensionTest, RegionAccessNorthSouth) {
    const unsigned int size = 3;
    int z, x = 1;
    for(z = -region_line_length_; z <= size; z++) {
        Region* region = dimension_->GetRegion(x,z);
        EXPECT_EQ(x, region->x());
        EXPECT_EQ(z, region->z());
    }
}

TEST_F(DimensionTest, RegionAccessEastWest) {
    const unsigned int size = 3;
    int x, z = 1;
    for(x = -region_line_length_; x <= size; x++) {
        Region* region = dimension_->GetRegion(x,z);
        EXPECT_EQ(x, region->x());
        EXPECT_EQ(z, region->z());
    }
}

TEST_F(DimensionTest, GetBlockPositive) {
    int x, y, z;
    for(x = 0; x <= size_; x++)
        for(y = 0; y <= size_; y++)
            for(z = 0; z <= size_; z++) {
                const int blockID = get_block_id(x,y,z);
                dimension_->SetBlock(x, y, z, blockID);
                EXPECT_EQ(blockID, dimension_->GetBlock(x, y, z));
            }
    int num_regions = dimension_->CountLoadedRegions();
    //EXPECT_TRUE(false) << "Number of active regions: " << num_regions << std::endl;
}

TEST_F(DimensionTest, GetBlockPositiveNegative) {
    int x, y, z;
    for(x = -size_; x <= size_; x++)
        for(y = 0; y <= size_; y++)
            for(z = -size_; z <= size_; z++) {
                const int blockID = get_block_id(x,y,z);
                EXPECT_EQ(blockID, dimension_->GetBlock(x, y, z));
            }
}


TEST_F(DimensionTest, GetSetBlockPositive) {
    Dimension* dim = new Dimension();
    int x, y, z;
    for(x = 0; x <= size_; x++)
        for(y = 0; y <= size_; y++)
            for(z = 0; z <= size_; z++) {
                const int blockID = get_block_id(x,y,z);
                dim->SetBlock(x, y, z, blockID);
                EXPECT_EQ(blockID, dim->GetBlock(x, y, z));
            }
    int num_regions = dim->CountLoadedRegions();
    delete dim;
    //EXPECT_TRUE(false) << "Number of active regions: " << num_regions << std::endl;
}

TEST_F(DimensionTest, GetSetBlockPositiveNegative) {
    Dimension* dim = new Dimension();
    int x, y, z;
    for(x = -size_; x <= size_; x++)
        for(y = 0; y <= size_; y++)
            for(z = -size_; z <= size_; z++) {
                const int blockID = get_block_id(x,y,z);
                dimension_->SetBlock(x, y, z, blockID);
                EXPECT_EQ(blockID, dimension_->GetBlock(x, y, z));
            }
    delete dim;
}

TEST_F(DimensionTest, GetRegionsAround) {
    const int max_dist = region_distance_;
    for(int distance = 0; distance < max_dist; distance++) {
        std::vector<Region *> regions_around_center = dimension_->GetRegionsAround(0, 0, distance);
        for (std::vector<Region *>::iterator it = regions_around_center.begin();
             it != regions_around_center.end(); ++it) {
            Region *r = (*it);
            //EXPECT_TRUE(false) << r->x() << "," << r->z() << std::endl;
        }
        EXPECT_EQ(regions_around_center.size(), (2 * distance + 1) * (2 * distance + 1));
    }
}

TEST_F(DimensionTest, GetRegionsAroundPrealloc) {
    const int max_dist = region_distance_;
    for(int distance = 0; distance < max_dist; distance++) {
        std::vector<Region *> regions_around_center = dimension_->GetRegionsAroundPrealloc(0, 0, distance);
        for (std::vector<Region *>::iterator it = regions_around_center.begin();
             it != regions_around_center.end(); ++it) {
            Region *r = (*it);
            //EXPECT_TRUE(false) << r->x() << "," << r->z() << std::endl;
        }
        EXPECT_EQ(regions_around_center.size(), (2 * distance + 1) * (2 * distance + 1));
    }
}


#endif