#include "path.hpp"

Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  for (size_t i = 0; i < length; i++) {
    path_.push_back(starting_row);
  }
  ele_change_ = 0;
}

size_t Path::StartingRow() const { 
	return starting_row_; 
}

const std::vector<size_t>& Path::GetPath() const { 
	return path_; 
}

void Path::SetLoc(size_t col, size_t row) { 
	path_.at(col) = row; 
}

size_t Path::EleChange() const { 
	return ele_change_; 
}

size_t Path::Length() const { 
	return length_; 
}

void Path::IncEleChange(unsigned int value) {
  if (value > 0) {
    ele_change_ += value;
  }
}