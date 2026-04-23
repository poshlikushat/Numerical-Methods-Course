#include <stdexcept>
#include "matrix_op.hpp"

std::vector<std::vector<double>> multiplyMatrices(
    const std::vector<std::vector<double>>& matrixA,
    const std::vector<std::vector<double>>& matrixB
)
{
    auto rowsA = matrixA.size();
    auto colsA = matrixA[0].size();
    auto rowsB = matrixB.size();
    auto colsB = matrixB[0].size();

    if (colsA != rowsB) {
        throw std::invalid_argument("Number of columns in A must match number of rows in B");
    }

    std::vector<std::vector<double>> result(rowsA, std::vector<double>(colsB, 0.0));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
	return result;
}
