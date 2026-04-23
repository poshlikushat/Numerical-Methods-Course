#include <algorithm>
#include <iostream>
#include "qr.hpp"
#include "matrix_op.hpp"

using std::pair;
using std::vector;

static pair<vector<double>, vector<vector<double>>> sort_by_eigenvalues(
	vector<double> eigenvalues,
	vector<vector<double>> V)
{
	auto n = eigenvalues.size();

	vector<int> idx(n);
	for (int i = 0; i < n; ++i) idx[i] = i;
	std::sort(idx.begin(), idx.end(), [&](int a, int b) {
			return eigenvalues[a] > eigenvalues[b];		// sort in descending order
		});

	vector<double> sorted_eigenvalues(n);
	for (int i = 0; i < n; ++i)
		sorted_eigenvalues[i] = eigenvalues[idx[i]];

	vector<vector<double>> sorted_V(n, vector<double>(n));
	for (int i = 0; i < n; ++i)         // rows
		for (int j = 0; j < n; ++j)     // cols
			sorted_V[i][j] = V[i][idx[j]];

	return { sorted_eigenvalues, sorted_V };
}

/*
	Gram-Schmidt process for QR decomposition of a matrix A into Q and R:
		1. Take j-th column of A as vector v.
		2. For each previous column k < j, subtract the projection of v onto Q's k-th column from v.
		3. Normalize v to get the j-th column of Q, and store the norm in R[j][j].
		4. v / || v || and store it in Q.
*/

pair<vector<vector<double>>, vector<vector<double>>> qr_decomposition(const vector<vector<double>>& A)
{
	auto num_rows = A.size();		// number of rows
	auto num_cols = A[0].size();		// number of columns

	vector<vector<double>> Q(num_rows, vector<double>(num_rows, 0.0));		// orthogonal matrix
	vector<vector<double>> R(num_rows, vector<double>(num_cols, 0.0));		// upper triangular matrix

	for (int k = 0; k < num_cols; ++k) {
		vector<double> v(num_rows, 0.0);

		for (int i = 0; i < num_rows; ++i) {
			v[i] = A[i][k];

			for (int j = 0; j < k; ++j) {
				v[i] -= R[j][k] * Q[i][j];
			}
		}

		double norm_v = 0.0;
		for (double val : v) {
			norm_v += val * val;
		}

		norm_v = sqrt(norm_v);
		if (norm_v > EPSILON) {		// divide by zero check
			for (int i = 0; i < num_rows; ++i) {
				Q[i][k] = v[i] / norm_v;
			}

			R[k][k] = norm_v;
			for (int j = k + 1; j < num_cols; ++j) {
				double dot_product = 0.0;

				for (int i = 0; i < num_rows; ++i) {
					dot_product += Q[i][k] * A[i][j];
				}
				R[k][j] = dot_product;
			}
		}
	}
	return { Q, R };
}

pair<vector<double>, vector<vector<double>>> qr_iterative(const vector<vector<double>>& C)
{
	auto V_size = C[0].size();
	auto A = C;
	vector<vector<double>> V;
	V.assign(V_size, vector<double>(V_size, 0.0));	// create elements with 0.0

	for (int i = 0; i < V_size; ++i) {
		V[i][i] = 1.0;
	}
	int iter = 0;
	while (iter != MAX_ITER) {
		auto [Q, R] = qr_decomposition(A);
		A = multiplyMatrices(R, Q);
		V = multiplyMatrices(V, Q);

		auto off_diagonal_sum = 0.0;
		auto diagonal_sum = 0.0;
		for (int i = 0; i < A.size(); ++i) {
			for (int j = 0; j < A[0].size(); ++j) {
				if (i != j) {
					off_diagonal_sum += A[i][j] * A[i][j];
				} else {
					diagonal_sum += A[i][j] * A[i][j];
				}
			}
		}
		if (off_diagonal_sum / diagonal_sum < CONVERGENCE) {
			break;
		}
		iter++;
	}
	auto eigenvalues = vector<double>(A.size(), 0.0);
	for (int i = 0; i < A.size(); ++i) {
		eigenvalues[i] = A[i][i];
	}
	return sort_by_eigenvalues(eigenvalues, V);
}
