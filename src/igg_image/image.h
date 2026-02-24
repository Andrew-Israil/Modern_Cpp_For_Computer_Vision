#pragma once

#include <vector>
#include <iostream>
#include "io_tools.h"

namespace igg {

class Image {
 public:
  Image(int rows=0, int cols=0);

  int rows() const;

  int cols() const;

  int& at(int row, int col);                  // get a pixel value

  const int& at(int row, int col) const;      // set a pixel value

  bool FillFromPgm(const std::string& file_name);

  void WriteToPgm(const std::string& file_name) const;

  std::vector<float> ComputeHistogram(int bins) const;

  void DownScale(int scale);

  void UpScale(int scale);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<int> data_;
};

}  // namespace igg
