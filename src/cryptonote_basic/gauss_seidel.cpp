#include "gauss_seidel.h"
#include <cmath>
#include <iostream>
#include <stdexcept>

GaussSeidel& GaussSeidel::instance() {
    static GaussSeidel solver; // Poprawna definicja singletona
    return solver;
}

std::vector<double> GaussSeidel::solve(const std::vector<std::vector<double>>& A, const std::vector<double>& b, int maxIterations, double tolerance) {
    int n = A.size();

    if (n == 0 || A[0].size() != n || b.size() != n) {
        throw std::invalid_argument("Macierz A musi być kwadratowa, a wektor b musi mieć odpowiedni rozmiar.");
    }

    std::vector<double> x(n, 0.0); 

    for (int k = 0; k < maxIterations; ++k) {
        std::vector<double> x_old = x;

        for (int i = 0; i < n; ++i) {
            double sum = 0.0;
            for (int j = 0; j < n; ++j) {
                if (i != j)
                    sum += A[i][j] * x[j];
            }
            if (A[i][i] == 0) {
                throw std::runtime_error("Element diagonalny macierzy A nie może być równy zero.");
            }
            x[i] = (b[i] - sum) / A[i][i];
        }

        double error = 0.0;
        for (int i = 0; i < n; ++i) {
            error += std::pow(x[i] - x_old[i], 2);
        }
        error = std::sqrt(error);

        std::cout << "Iteracja " << k + 1 << ", błąd: " << error << std::endl;

        if (error < tolerance) {
            std::cout << "Zbieżność osiągnięta po " << k + 1 << " iteracjach." << std::endl;
            return x;
        }
    }

    std::cerr << "Ostrzeżenie: Brak zbieżności po maksymalnej liczbie iteracji." << std::endl;
    return x;
}

double GaussSeidel::adjust_difficulty(double base_difficulty) {
    return base_difficulty * 0.9;
}
