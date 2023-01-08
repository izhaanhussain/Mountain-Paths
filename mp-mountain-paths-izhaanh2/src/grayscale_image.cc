#include "grayscale_image.hpp"
#include "color.hpp"
#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
    height_ = dataset.Height();
    width_ = dataset.Width();
    std::vector<std::vector<Color>> vec( dataset.Height() , std::vector<Color> (dataset.Width()));
    image_ = vec;
    for (unsigned int i = 0; i < height_; ++i) {
        for (unsigned int j = 0; j < width_; ++j) {
            int datum = dataset.GetData()[i][j];
            int shade = (int)std::round(kMaxColorValue * (double)(datum - dataset.MinEle()) / (double)(dataset.MaxEle() - dataset.MinEle()));
            image_[i][j] = Color(shade, shade, shade);
        }
    }
}

GrayscaleImage::GrayscaleImage(const std::string& filename, size_t width, size_t height) {
    ElevationDataset dataset(filename, width, height);
    height_ = dataset.Height();
    width_ = dataset.Width();
    std::vector<std::vector<Color>> vec( dataset.Height() , std::vector<Color> (dataset.Width()));
    image_ = vec;
    for (unsigned int i = 0; i < height_; ++i) {
        for (unsigned int j = 0; j < width_; ++j) {
            int datum = dataset.GetData()[i][j];
            int shade = (int)std::round(kMaxColorValue * (double)(datum - dataset.MinEle()) / (double)(dataset.MaxEle() - dataset.MinEle()));
            image_[i][j] = Color(shade, shade, shade);
        }
    }
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
    int height = height_;
    int width = width_;
	if (row < 0 || row > height || col < 0 || col > width) {
		throw std::invalid_argument("");
	}
	return image_[row][col];
}

void GrayscaleImage::ToPpm( const std::string& name ) const { 
	std::ofstream ofs{name};
    ofs << "P3" << '\n' << width_ << " " << height_ << '\n' << kMaxColorValue << '\n';
    for (unsigned int i = 0; i < height_; ++i) {
        for (unsigned int j = 0; j < width_; ++j) {
            ofs << image_[i][j].Red() << " " << image_[i][j].Green() << " " << image_[i][j].Blue() << " ";
        }
        ofs << '\n';
    }
}

size_t GrayscaleImage::Width() const {
    return width_;
}
size_t GrayscaleImage::Height() const {
    return height_;
}

unsigned int GrayscaleImage::MaxColorValue() const {
    return kMaxColorValue;
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
    return image_;
}