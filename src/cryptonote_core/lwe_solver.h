#ifndef LWE_SOLVER_H
#define LWE_SOLVER_H

#include <vector>

class LWESolver {
public:
    LWESolver(const std::vector<std::vector<int>>& A, const std::vector<int>& b);
    std::vector<int> solve();

private:
    std::vector<std::vector<int>> A;
    std::vector<int> b;
};

#endif // LWE_SOLVER_H