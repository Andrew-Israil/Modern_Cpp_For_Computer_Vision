#pragma once

#include <vector>
#include <iostream>
#include "igg_image/io_strategies/strategy.h"

namespace igg {

class RGBImage {
 public:
  
  struct Pixel {
    int red;
    int green;
    int blue;
  };

  RGBImage(int rows, int cols, const IoStrategy& io_strategy);

  RGBImage(const IoStrategy& io_strategy);

  int rows() const;

  int cols() const;

  Pixel& at(int row, int col);                  // get a pixel value

  const Pixel& at(int row, int col) const;      // set a pixel value

  bool ReadFromDisk(const std::string& file_name);

  void WriteToDisk(const std::string& file_name) const;

  std::vector<std::vector<float>> ComputeHistogram(int bins) const;

  void DownScale(int scale);

  void UpScale(int scale);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<Pixel> data_;
  const IoStrategy& strategy_;
};

}  // namespace igg
