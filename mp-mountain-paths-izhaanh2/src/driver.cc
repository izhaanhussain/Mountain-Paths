#include <iostream>
#include "color.hpp"
#include "path.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main() {
    ElevationDataset data("example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);
    GrayscaleImage gray(data);
    PathImage pathimg(gray, data);
    pathimg.ToPpm("example.ppm");
    // for (unsigned int i = 0; i < data.Height(); ++i) {
    //     for (unsigned int j = 0; j < data.Width(); ++j) {
    //         std::cout << data.DatumAt(i,j) << " ";
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << gray.ColorAt(0, 0).Red() << " " << gray.ColorAt(0, 0).Green() << " " << gray.ColorAt(0, 0).Blue() << std::endl;
    // std::cout << gray.getShade(data, 0, 0) << " " << gray.getShade(data, 0, 0) << " " << gray.getShade(data, 0, 0) << std::endl;
}

// size_t previous_row = temp.GetPath()[j - 1];           
//             int data = dataset.DatumAt(previous_row, j - 1);
//             int top = abs(dataset.DatumAt(previous_row - 1, j) - data);
//             int middle = abs(dataset.DatumAt(previous_row, j) - data);
//             int bottom = abs(dataset.DatumAt(previous_row + 1, j) - data);
//             std::cout << dataset.DatumAt(previous_row - 1, j) << " " << dataset.DatumAt(previous_row + 1, j) << " ";
//             // std::cout << dataset.DatumAt(previous_row, j) << std::endl;
//             tester = bottom;
//             if (middle <= top/* && middle <= bottom*/) {
//                 temp.SetLoc(j, previous_row);
//                 temp.IncEleChange(abs(data - middle));
//             } /*else if (bottom < middle && bottom <= top) {
//                 temp.SetLoc(j, previous_row + 1);
//                 temp.IncEleChange(abs(data - bottom));
//             }*/ else if (top < middle) {
//                 temp.SetLoc(j, previous_row - 1);
//                 temp.IncEleChange(abs(data - top));
//             }