#include "io.hpp"
#include "ising_complexity.hpp"
#include <random>

// TODO: add error estimation
// TODO: refactoring (Monte Carlo in separate function, parallel)
int main() {
  const unsigned long L = 30; // Linear size of square matrix
  const unsigned long n_steps = 300000;
  const unsigned long num_mean_iter = 3;
  const double T_init = 5.0;
  const double T_final = 0.0;
  const double T_step = 0.01;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, L - 1);

  std::random_device rd1;
  std::mt19937 gen1(rd1());
  std::uniform_real_distribution<> dist1(0, 1);

  std::vector<std::vector<double>> complexities_for_mean(num_mean_iter);
  std::vector<std::vector<double>> temperatures_for_mean(num_mean_iter);

  for (unsigned long iter = 0; iter < num_mean_iter; iter++) {
    Matrix grid = gen_matrix(L);
    std::vector<double> complexities;
    std::vector<double> temperatures;
    for (double T = T_init; T > T_final; T -= T_step) {
      for (unsigned long i = 0; i < n_steps; i++) {
        const unsigned long x = dist(gen);
        const unsigned long y = dist(gen);
        const double dE = get_delta_energy(grid, x, y);
        grid[x][y] *= -1;
        if (dE > 0) {
          if (dist1(gen1) >= std::exp(-dE / T)) {
            grid[x][y] *= -1;
          }
        }
      }
      Matrix temp_grid(grid); // copy
      complexities.push_back(find_structural_complexity(temp_grid, 2));
      temperatures.push_back(T);
    }
    complexities_for_mean[iter] = complexities;
    temperatures_for_mean[iter] = temperatures;
  }

  std::vector<double> complexities(T_init / T_step);
  std::vector<double> temperatures(T_init / T_step);
  for (unsigned long iter = 0; iter < T_init / T_step; iter++) {
    double c_sum = 0.0;
    double t_sum = 0.0;
    for (unsigned long i = 0; i < num_mean_iter; i++) {
      c_sum += complexities_for_mean[i][iter];
      t_sum += temperatures_for_mean[i][iter];
    }
    complexities[iter] = c_sum / num_mean_iter;
    temperatures[iter] = t_sum / num_mean_iter;
  }
  write_vecs(temperatures, complexities);
}
