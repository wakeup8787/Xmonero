#ifndef LWE_SOLVER_H
#define LWE_SOLVER_H

#include <vector>

namespace cryptonote {

class LWESolver {
public:
    // Konstruktor otrzymujący macierz A oraz wektor b
    LWESolver(const std::vector<std::vector<int>>& A, const std::vector<int>& b);

    // Rozwiązuje układ równań A*x = b metodą iteracyjną
    std::vector<int> solve();

    // Oblicza współczynnik trudności na podstawie rozwiązania (przykładowa implementacja)
    double calculate_difficulty_factor();

    // Metoda singleton – zwraca domyślną instancję solvera
    static LWESolver& instance() {
         // Przykładowe domyślne dane – w praktyce tutaj należy wstawić dane dotyczące puzzli
         static std::vector<std::vector<int>> defaultA = { {1, 0}, {0, 1} };
         static std::vector<int> defaultB = { 1, 1 };
         static LWESolver instance(defaultA, defaultB);
         return instance;
    }

private:
    std::vector<std::vector<int>> A;
    std::vector<int> b;
};

} // namespace cryptonote

#endif // LWE_SOLVER_H
