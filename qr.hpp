#include <vector>

constexpr double EPSILON = 1e-10;
constexpr int MAX_ITER = 10000;
constexpr double CONVERGENCE = 1e-12;

std::pair<std::vector<std::vector<double>>, std::vector<std::vector<double>>>
qr_decomposition(const std::vector<std::vector<double>>& A);

std::pair<std::vector<double>, std::vector<std::vector<double>>> qr_iterative(const std::vector<std::vector<double>>& A);