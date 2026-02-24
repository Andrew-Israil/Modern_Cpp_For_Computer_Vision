#include "image.h"

namespace igg {

    Image::Image(int rows=0, int cols=0)
    : rows_{rows}, cols_{cols} 
    {
        data_.reserve(rows*cols);
    }

    int Image::rows() const { return rows_;}

    int Image::cols() const { return cols_;}

    int& Image::at(int row, int col)
    {
        std::size_t index{static_cast<std::size_t>( (row*cols_) + col )};
        return data_[index];
    }

     const int& Image::at(int row, int col) const
     {
        std::size_t index{static_cast<std::size_t>( (row*cols_) + col )};
        return data_[index];
    }

    bool Image::FillFromPgm(const std::string& file_name)
    {
        io_tools::ImageData img{ io_tools::ReadFromPgm(file_name)};

        if(img.data.empty()){
            return false;
        }

        this->rows_ = img.rows;
        this->cols_ = img.cols;
        this->max_val_ = img.max_val;
        this->data_ = std::move(img.data);
        return  true;
    }

    void Image::WriteToPgm(const std::string& file_name) const
    {
        io_tools::ImageData img{this->rows_, this->cols_, this->max_val_, this->data_};
        io_tools::WriteToPgm(img, file_name);
    }

    std::vector<float> Image::ComputeHistogram(int bins) const
    {
        if(bins <= 0){
            std::cout << "invalid bins number";
            return {};
        }
        
        std::vector<float> histogram(bins);

        int bin_width = (this->max_val_ + 1) / bins;

        for(auto& pixel : this->data_){
            int bin = pixel / bin_width;
            histogram[bin]++;
        }

        float  data_size = static_cast<float>(this->data_.size());
        for(float& bin : histogram){
            bin /= data_size;
        }

        return histogram;
    }

    void Image::DownScale(int scale)
    {
        int scaled_rows = this->rows_ / scale;
        int scaled_cols = this->cols_ / scale;

        std::vector<int> new_data(scaled_rows * scaled_cols);

        for(int i=0; i<this->rows_; i+=scale){
            for(int j=0; j<this->cols_; j+=scale){
                new_data.push_back(this->at(i,j));
            }
        }

        this->rows_ = scaled_rows;
        this->cols_ = scaled_cols;
        this->data_ = std::move(new_data);
    }

    void Image::UpScale(int scale)
    {
        int scaled_rows = this->rows_ * scale;
        int scaled_cols = this->cols_ * scale;

        std::vector<int> new_data(scaled_rows * scaled_cols);

        
        for(int r = 0; r < scaled_rows; ++r){
            for(int c = 0; c < scaled_cols; ++c){
                int nn_row = r / scale;
                int nn_col = c / scale;
                new_data[(r * scaled_cols) + c] = this->data_[(nn_row * this->cols_) + nn_col];
            }
        }

        this->rows_ = scaled_rows;
        this->cols_ = scaled_cols;
        this->data_ = std::move(new_data);
    }

} // namespace igg