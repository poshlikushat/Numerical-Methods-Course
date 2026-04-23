#include <stdexcept>
#include "csv_parcer.hpp"

std::vector<std::vector<double>> read_csv(const std::string& filename, int rows, int cols)
{
	std::vector<std::vector<double>> B(rows, std::vector<double>(cols));
	std::ifstream file(filename);
	if (!file) {
		throw std::runtime_error("Could not open file: " + filename);
	}
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			file >> B[i][j];
			if (file.peek() == ',') file.ignore();
		}
	}
	return B;
}