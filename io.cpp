#pragma once
#include "io.hpp"
#include <fstream>
#include <iostream>

void print_matrix(const Matrix &vec) {
  for (auto &row : vec) {
    for (auto &n : row) {
      std::cout /* << std::setw(2) */ << n << ' ';
    }
    std::cout << '\n';
  }
}

void write_vecs(const std::vector<double> &vec1,
                const std::vector<double> &vec2) {
  std::ofstream outfile("data.txt");
  if (outfile.is_open()) {
    for (std::size_t i = 0; i < vec1.size(); i++) {
      outfile << vec1[i] << ' ' << vec2[i] << '\n';
    }
    outfile.close();
  } else {
    std::cerr << "Failed open file for write\n";
  }
}
