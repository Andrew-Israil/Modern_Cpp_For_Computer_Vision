#include <gtest/gtest.h>
#include "igg_image/image.h"

/*****************  Constructors Test ***************/
TEST(ImageTest, DefaultConstructor){
    igg::Image img;
    EXPECT_EQ(img.rows(), 0);
    EXPECT_EQ(img.cols(), 0);
}

TEST(ImageTest, ParametrizedConstructor){
    igg::Image img(3, 4);
    EXPECT_EQ(img.rows(), 3);
    EXPECT_EQ(img.cols(), 4);
}

/*************** Pixels Access ************************/
TEST(ImageTest, AtSetAndGetPixel) {
    igg::Image img(2, 2);

    img.at(0, 0) = 10;
    img.at(0, 1) = 20;
    img.at(1, 0) = 30;
    img.at(1, 1) = 40;

    EXPECT_EQ(img.at(0,0), 10);
    EXPECT_EQ(img.at(0,1), 20);
    EXPECT_EQ(img.at(1,0), 30);
    EXPECT_EQ(img.at(1,1), 40);
}

TEST(ImageTest, ConstAtAccess) {
    igg::Image img(1, 1);
    img.at(0,0) = 99;

    const igg::Image& const_img = img;

    EXPECT_EQ(const_img.at(0,0), 99);
}

/***************** Histogram Test **********************/
TEST(ImageTest, ComputeHistogramBasic) {
    igg::Image img(2,2);

    img.at(0,0) = 0;
    img.at(0,1) = 0;
    img.at(1,0) = 255;
    img.at(1,1) = 255;

    auto hist = img.ComputeHistogram(2);

    ASSERT_EQ(hist.size(), 2);

    // Expect equal distribution
    EXPECT_FLOAT_EQ(hist[0], 0.5f);
    EXPECT_FLOAT_EQ(hist[1], 0.5f);
}

/******************* Image Downscaling Test *******************/
TEST(ImaeTest, DownScaleReducesSize){
    igg::Image img(4,4);

    for(int r = 0; r < 4; ++r){
        for(int c = 0; c < 4; ++c){
            if((r < 2 && c < 2) || (r >=2 && c >= 2)){
                img.at(r,c) = 255;
            }
            else{
                img.at(r,c) = 0;
            }
        }
    }

    img.DownScale(2);

    ASSERT_EQ(img.rows(),2);
    ASSERT_EQ(img.cols(),2);

    EXPECT_EQ(img.at(0,0), 255);
    EXPECT_EQ(img.at(1,1), 255);
    EXPECT_EQ(img.at(0,1), 0);
    EXPECT_EQ(img.at(1,0), 0);
}

/******************* Image Upscaling Test *******************/
TEST(ImaeTest, UpScaleReducesSize){
    igg::Image img(2,2);

    img.at(0,0) = 255;
    img.at(0,1) = 0;
    img.at(1,0) = 0;
    img.at(1,1) = 255;

    img.UpScale(2);

    ASSERT_EQ(img.rows(),4);
    ASSERT_EQ(img.cols(),4);

    for(int r = 0; r < 4; ++r){
        for(int c = 0; c < 4; ++c){
            if((r < 2 && c < 2) || (r >=2 && c >= 2)){
                EXPECT_EQ(img.at(r,c), 255);
            }
            else{
                EXPECT_EQ(img.at(r,c), 0);
            }
        }
    }
}