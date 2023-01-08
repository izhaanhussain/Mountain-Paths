#include "elevation_dataset.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename, size_t width, size_t height):
    width_(width), height_(height) {
  std::ifstream ifs{filename};
  int max = 0;
  int min = 0;
  std::vector<int> temp;
  if (!ifs.is_open()) {
    throw std::runtime_error("");
  }
  for (std::string line; std::getline(ifs, line); line = "") {
    size_t last = 0;
    for (size_t i = 0; i != line.length(); i++) {
      if (line.at(i) == ' ') {
        std::string each = line.substr(last, i - last);
        if (each.empty()) {
          last = i + 1;
          continue;
        }
        last = i + 1;
        temp.push_back(stoi(each));
      }
    }
    std::string str = line.substr(last, line.length() - last);
    if (!str.empty()) temp.push_back(stoi(str));
  }
  if (temp.size() != width_ * height_) {
    throw std::runtime_error("");
  }
  GetNums(temp, max, min);
  max_ele_ = max;
  min_ele_ = min;
  int counter = 0;
  for (size_t row = 0; row < height_; row++) {
    std::vector<int> tmp;
    for (size_t col = 0; col < width_; col++) {
      tmp.push_back(temp.at(counter));
      counter++;
    }
    data_.push_back(tmp);
  }
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}

size_t ElevationDataset::Width() const { 
  return width_; 
}

int ElevationDataset::MaxEle() const { 
  return max_ele_; 
}

int ElevationDataset::MinEle() const {
  return min_ele_; 
}

size_t ElevationDataset::Height() const {
  return height_; 
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}

void GetNums(const std::vector<int>& vec, int& max, int& min) {
  max = vec.at(0);
  max = vec.at(0);
  for (size_t i = 0; i < vec.size(); ++i) {
    if (vec.at(i) > max) {
      max = vec.at(i);
    } 
    if (vec.at(i) < min) {
      min = vec.at(i);
    }
  }
}