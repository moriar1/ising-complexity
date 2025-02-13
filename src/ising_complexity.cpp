#include "ising_complexity.hpp"
#include <numeric>
#include <random>

// Helper function for averaging values in L by L blocks in `mat`
void renorm(Matrix &mat, const unsigned long L) {
  const unsigned long nblock = mat.size() / L;

  // Iterate by blocks
  for (std::size_t outer = 0; outer < nblock; outer++) {
    for (std::size_t inner = 0; inner < nblock; inner++) {
      double sum = 0.0;
      for (std::size_t i = outer * L; i < L * (outer + 1); i++) {
        for (std::size_t j = inner * L; j < L * (inner + 1); j++) {
          sum += mat[i][j];
        }
      }
      double mean = sum / (L * L);
      for (std::size_t i = outer * L; i < L * (outer + 1); i++) {
        for (std::size_t j = inner * L; j < L * (inner + 1); j++) {
          mat[i][j] = mean;
        }
      }
    }
  }
}

// Helper function
[[nodiscard]]
double find_matrix_mean(const Matrix &mat) {
  double sum = 0.0;
  for (unsigned long i = 0; i < mat.size(); i++) {
    sum += std::accumulate(mat[i].begin(), mat[i].end(), 0.0);
  }
  return sum / (mat.size() * mat.size());
}

[[nodiscard]]
double find_overlap(Matrix mat1, Matrix mat2) {
  // assert(mat1.size() == mat2.size());
  double sum = 0.0;
  for (std::size_t i = 0; i < mat1.size(); i++) {
    for (std::size_t j = 0; j < mat1.size(); j++) {
      sum += mat1[i][j] * mat2[i][j];
    }
  }
  return sum / (mat1.size() * mat1.size());
}

[[nodiscard]]
double find_structural_complexity(Matrix &mat, unsigned long lambda) {
  // assert(mat.size() % lambda == 0 && mat[0].size() == mat.size());

  std::size_t n_overlaps = std::log(mat.size()) / std::log(lambda);
  double sum = 0.;

  for (std::size_t i = 0; i < n_overlaps; i++) {
    Matrix mat_old(mat);
    renorm(mat, lambda); // changes `mat`
    sum += std::abs(
        find_overlap(mat_old, mat) -
        0.5 * (find_overlap(mat, mat) + find_overlap(mat_old, mat_old)));
    lambda *= 2; // Increasing block size
  }

  return sum;
}

[[nodiscard]]
Matrix gen_matrix(const unsigned long L) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dist(0.0, 1.0);
  Matrix matrix(L, std::vector<double>(L));
  for (auto &row : matrix) {
    for (auto &n : row) {
      n = dist(gen) > 0.5 ? 1 : -1;
    }
  }
  return matrix;
}

[[nodiscard]]
double get_delta_energy(Matrix &grid, const unsigned long x,
                        const unsigned long y) {
  const std::size_t L = grid.size();

  // Using periodic boundary condition
  const unsigned long right_x = (x + 1) % L;
  const unsigned long left_x = x == 0 ? L - 1 : x - 1;
  const unsigned long top_y = (y + 1) % L;
  const unsigned long bot_y = y == 0 ? L - 1 : y - 1;

  // Each spin is connected only with its neighbors
  return 2 * grid[x][y] *
         (grid[right_x][y] + grid[left_x][y] + grid[x][top_y] + grid[x][bot_y]);
}
