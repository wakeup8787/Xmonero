#include "lwe_solver.h"
#include <iostream>
#include <cmath>

namespace cryptonote {

LWESolver::LWESolver(const std::vector<std::vector<int>>& A, const std::vector<int>& b)
    : A(A), b(b) {}

std::vector<int> LWESolver::solve() {
    int n = A.size();
    std::vector<int> x(n, 0); // Inicjalizacja wektora rozwiązań zerami
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
            // Prosta aktualizacja – dla przykładu (należy uważać przy dzieleniu przez zero)
            x[i] = sum / A[i][i];
        }

        // Sprawdzenie czy rozwiązanie się ustabilizowało
        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::abs(x[i] - x_old[i]);
        }
        if (error < tolerance) break;
    }

    return x;
}

double LWESolver::calculate_difficulty_factor() {
    // Przykładowa logika: rozwiązujemy układ, sumujemy wartości i zwracamy średnią
    std::vector<int> solution = solve();
    double sum = 0.0;
    for (int v : solution)
        sum += v;
    double factor = sum / (solution.empty() ? 1 : solution.size());
    return factor;
}

} // namespace cryptonote
