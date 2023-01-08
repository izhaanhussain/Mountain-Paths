#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include <cstdlib>  // for size_t
#include <vector>
#include <string>


class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage &image, const ElevationDataset &dataset);
  size_t Width() const;
  size_t Height() const;
  size_t MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color> >& GetPathImage() const;
  void ToPpm(const std::string& name) const;
  size_t SolveTop(std::vector<std::vector<int>> vec, size_t row, size_t col);
  size_t SolveBottom(std::vector<std::vector<int>> vec, size_t row, size_t col);
  size_t SolveMiddle(std::vector<std::vector<int>> vec, size_t row, size_t col);
  Path GetBest();
private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
};

#endif