#include "lwe_solver.h"
#include <iostream>
#include <cmath>

LWESolver::LWESolver(const std::vector<std::vector<int>>& A, const std::vector<int>& b)
    : A(A), b(b) {}

std::vector<int> LWESolver::solve() {
    int n = A.size();
    std::vector<int> x(n, 0); // Wektor rozwiązań, inicjalizowany zerami
    double tolerance = 1e-6;  // Warunek stopu
    int max_iterations = 1000;

    for (int iter = 0; iter < max_iterations; ++iter) {
        std::vector<int> x_old = x;

        for (int i = 0; i < n; ++i) {
            int sum = b[i];

            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i]; // Aktualizacja wartości x[i]
        }

        // Sprawdzamy, czy rozwiązanie się ustabilizowało
        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::abs(x[i] - x_old[i]);
        }
        if (error < tolerance) break;
    }

    return x;
}
