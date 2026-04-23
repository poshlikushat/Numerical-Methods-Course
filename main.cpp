#include <iostream>
#include <iomanip>
#include "qr.hpp"
#include "matrix_op.hpp"
#include "csv_parcer.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    try {
        std::string data_dir = argc > 1 ? argv[1] : ".";
        auto C = read_csv(data_dir + "/a.csv", 4, 4);
        auto B = read_csv(data_dir + "/b.csv", 30, 4);

        auto [eigenvalues, V] = qr_iterative(C);

        double total = 0.0;
        for (double e : eigenvalues) total += e;

        std::cout << "=== Eigenvalues and variance shares ===\n";
        for (auto i = 0; i < eigenvalues.size(); ++i)
            std::cout << "lambda[" << i << "] = " << std::setw(10) << std::fixed << std::setprecision(4)
            << eigenvalues[i] << "  share = "
            << eigenvalues[i] / total * 100 << "%\n";
        std::cout << "Total variance: " << total << "\n\n";

        std::cout << "=== Matrix V (eigenvectors) ===\n";
        for (auto& row : V) {
            for (double x : row)
                std::cout << std::setw(10) << std::fixed << std::setprecision(4) << x;
            std::cout << "\n";
        }

        // проекция B_tilde = B * V
        auto B_tilde = multiplyMatrices(B, V);

        std::cout << "\n=== Projection B_tilde = B * V ===\n";
        for (auto& row : B_tilde) {
            for (double x : row)
                std::cout << std::setw(10) << std::fixed << std::setprecision(4) << x;
            std::cout << "\n";
        }

        return 0;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
		return 1;
    }
}
