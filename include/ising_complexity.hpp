#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;

double find_structural_complexity(Matrix &mat, unsigned long lambda);
double find_overlap(Matrix mat1, Matrix mat2);

// Generation L by L matrix of 1 and -1
Matrix gen_matrix(const unsigned long L);
double get_delta_energy(Matrix &grid, const unsigned long x,
                        const unsigned long y);
