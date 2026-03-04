#include <gtest/gtest.h>
#include "igg_image/io_strategies/ppm_strategy.h"

TEST(PPMStrategy, ReadImage){
    const igg::PpmIoStrategy str;
    igg::ImageData img{str.Read("../../data/pbmlib.ascii.ppm")};
    ASSERT_EQ(img.rows, 300);
    ASSERT_EQ(img.cols, 300);
    ASSERT_EQ(img.max_val, 255);
    ASSERT_EQ(img.data[0].size(), 300*300);
    ASSERT_EQ(img.data[1].size(), 300*300);
    ASSERT_EQ(img.data[2].size(), 300*300);
    ASSERT_EQ(img.data[0][0], 255);
}

TEST(PPMStrategy, WriteImage){
    const igg::PpmIoStrategy str;
    igg::ImageData img{str.Read("../../data/pbmlib.ascii.ppm")};
    ASSERT_EQ(str.Write("../../data/pbmlib_copy.ascii.ppm", img), true);
    igg::ImageData img_copy{str.Read("../../data/pbmlib_copy.ascii.ppm")};
    EXPECT_EQ(img.rows, img_copy.rows);
    EXPECT_EQ(img.cols, img_copy.cols);
    EXPECT_EQ(img.max_val, img_copy.max_val);
    EXPECT_EQ(img.data[0].size(), img_copy.data[0].size());
    EXPECT_EQ(img.data[1].size(), img_copy.data[1].size());
    EXPECT_EQ(img.data[2].size(), img_copy.data[2].size());
    EXPECT_EQ(img.data[0][0], img_copy.data[0][0]);
}