#include "path_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

PathImage::PathImage(const GrayscaleImage& image, const ElevationDataset& dataset) {
  std::vector<std::vector<int>> data = dataset.GetData();
  const Color kRed = Color(252, 25, 63);
  const Color kGreen = Color(31, 253, 13);
  width_ = dataset.Width();
  height_ = dataset.Height();
  std::vector<std::vector<Color>> gray_image = image.GetImage();
  for (size_t i = 0; i < height_; i++) {
    Path p(width_, i);
    size_t counter = i;
    gray_image.at(i).at(0) = kRed;
    for (size_t j = 1; j < width_; j++) {
      size_t curr = counter;
      int previous = data.at(counter).at(j - 1);
      int current = abs(previous - data.at(counter).at(j));
      if (curr != height_ - 1) {
        int up = abs(previous - data.at(curr + 1).at(j));
        if (up < current) {
          current = up;
          counter = curr + 1;
        }
      }
      if (curr != 0) {
        int up = abs(previous - data.at(curr - 1).at(j));
        if (up < current) {
          current = up;
          counter = curr - 1;
        }
      }
      p.SetLoc(j, counter);
      p.IncEleChange(current);
      gray_image.at(counter).at(j) = kRed;
    }
    paths_.push_back(p);
  }
  Path best_path_row = GetBest();
    for(size_t col = 0; col < best_path_row.Length(); col++) {
        gray_image[best_path_row.GetPath()[col]][col] = kGreen;
    }	
  path_image_ = gray_image;
}

const std::vector<Path>& PathImage::Paths() const { 
    return paths_; 
}

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

size_t PathImage::Width() const { 
    return width_; 
}

size_t PathImage::Height() const { 
    return height_; 
}

size_t PathImage::MaxColorValue() const { 
    return kMaxColorValue; 
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs{name};
  ofs << "P3" << "\n" << width_ << " " << height_ << "\n" << "255" << std::endl;
  for (size_t i = 0; i < height_; i++) {
    std::string temp;
    for (size_t j = 0; j < width_; j++) {
      Color color = path_image_.at(i).at(j);
      ofs << color.Red() << " " << color.Green() << " " << color.Blue() << " ";
    }
    ofs << '\n';
  }
}

Path PathImage::GetBest() {
    Path best_path_row = paths_[0];
    for(Path p : paths_) {
        if(p.EleChange() <= best_path_row.EleChange()) {
            best_path_row = p;
        }
    }
    return best_path_row;
}