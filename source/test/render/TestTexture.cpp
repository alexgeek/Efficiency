#include <iostream>
#include "gtest/gtest.h"
#include "../../src/render/Texture.h"

TEST(TestTexture, TextureTest)
{
    int size;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size);
    EXPECT_TRUE(true) << "MAX TEX SIZE = " << size << std::endl;
}