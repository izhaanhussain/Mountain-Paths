#ifndef PATH_H
#define PATH_H

#include <cstdlib>  // for size_t
#include <vector>
#include <stdexcept>

class Path {
public:
  Path(size_t length, size_t starting_row);
  size_t Length() const;
  size_t StartingRow() const;
  size_t EleChange() const;
  void IncEleChange(unsigned int value);
  const std::vector<size_t>& GetPath() const;
  void SetLoc( size_t col, size_t row );
private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_;
};

#endif