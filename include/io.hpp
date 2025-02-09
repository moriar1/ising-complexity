#pragma once
#include <vector>
using Matrix = std::vector<std::vector<double>>;

void print_matrix(const Matrix &mat);

// Function for writing two vectors to the file "data.txt" by columns
// vec1[i] vec2[i]
void write_vecs(const std::vector<double> &vec1,
                const std::vector<double> &vec2);
