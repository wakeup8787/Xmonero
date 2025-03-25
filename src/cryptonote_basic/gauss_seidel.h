#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

#include <vector>

class GaussSeidel {
public:
    /**
     * Rozwiązuje układ równań liniowych Ax = b metodą Gaussa-Seidla.
     * 
     * @param A Macierz współczynników (kwadratowa).
     * @param b Wektor wyrazów wolnych.
     * @param maxIterations Maksymalna liczba iteracji.
     * @param tolerance Tolerancja błędu dla rozwiązania.
     * @return Wektor rozwiązania x.
     */
    static std::vector<double> solve(const std::vector<std::vector<double>>& A, const std::vector<double>& b, int maxIterations, double tolerance);

    /**
     * Korekta trudności na podstawie bazowej trudności.
     * 
     * @param base_difficulty Bazowa trudność.
     * @return Skorygowana trudność.
     */
    static double adjust_difficulty(double base_difficulty);

    /**
     * Zwraca instancję singletona klasy GaussSeidel.
     * @return Referencja do instancji klasy GaussSeidel.
     */
    static GaussSeidel& instance();
};

#endif // GAUSS_SEIDEL_H
