#include "rgb_image.h"

namespace igg {

    RGBImage::RGBImage(int rows, int cols, const IoStrategy& io_strategy)
        : strategy_{io_strategy}
    {
        if(rows > 0 && cols > 0){
            rows_ = rows;
            cols_ = cols;
        }

        data_.resize(rows_*cols_);
    }

    int RGBImage::rows() const { return rows_;}

    int RGBImage::cols() const { return cols_;}

    RGBImage::Pixel& RGBImage::at(int row, int col)
    {
        std::size_t index{static_cast<std::size_t>( (row*cols_) + col )};
        return data_[index];
    }

     const  RGBImage::Pixel& RGBImage::at(int row, int col) const
     {
        std::size_t index{static_cast<std::size_t>( (row*cols_) + col )};
        return data_[index];
    }

    bool RGBImage::FillFromPgm(const std::string& file_name)
    {
        // io_tools::ImageData img{ io_tools::ReadFromPgm(file_name)};

        // if(img.data.empty()){
        //     std::cout<<"Tried to fill image from empty file" << std::endl;
        //     return false;
        // }

        // this->rows_ = img.rows;
        // this->cols_ = img.cols;
        // this->max_val_ = img.max_val;
        // this->data_ = std::move(img.data);
        return  true;
    }

    void RGBImage::WriteToPgm(const std::string& file_name) const
    {
        // io_tools::ImageData img{this->rows_, this->cols_, this->max_val_, this->data_};
        // io_tools::WriteToPgm(img, file_name);
    }

    std::vector<std::vector<float>> RGBImage::ComputeHistogram(int bins) const
    {
        if(bins <= 0){
            std::cout << "invalid bins number";
            return {};
        }

        if(data_.empty()){
            std::cout << "Empty image, can not calculate Histogram";
            return {};
        }

        enum Color{RED, GREEN, BLUE};
        
        std::vector<std::vector<float>> histogram(3);
        histogram[RED].resize(bins);
        histogram[GREEN].resize(bins);
        histogram[BLUE].resize(bins);

        int bin_width = (max_val_ + 1) / bins;

        for(auto& pixel : this->data_){
            int bin_red = pixel.red / bin_width;
            int bin_green = pixel.green / bin_width;
            int bin_blue = pixel.blue / bin_width;
            if (bin_red >= bins)
                bin_red = bins - 1;
            if (bin_green >= bins)
                bin_green = bins - 1;
            if (bin_blue >= bins)
                bin_blue = bins - 1;

            histogram[RED][bin_red]++;
            histogram[GREEN][bin_green]++;
            histogram[BLUE][bin_blue]++;
        }

        float  data_size = static_cast<float>(data_.size());
        for(int i = 0; i < 3; ++i){
            for(float& bin : histogram[i]){
                bin /= data_size;
            }
        }

        return histogram;
    }

    void RGBImage::DownScale(int scale)
    {
        int scaled_rows = this->rows_ / scale;
        int scaled_cols = this->cols_ / scale;

        std::vector<RGBImage::Pixel> new_data;
        new_data.reserve(scaled_rows * scaled_cols);

        for(int i=0; i<this->rows_; i+=scale){
            for(int j=0; j<this->cols_; j+=scale){
                new_data.push_back(this->at(i,j));
            }
        }

        this->rows_ = scaled_rows;
        this->cols_ = scaled_cols;
        this->data_ = std::move(new_data);
    }

    void RGBImage::UpScale(int scale)
    {
        int scaled_rows = this->rows_ * scale;
        int scaled_cols = this->cols_ * scale;

        std::vector<RGBImage::Pixel> new_data;
        new_data.reserve(scaled_rows * scaled_cols);

        
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