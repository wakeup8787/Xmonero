#pragma once

#include "cryptonote_basic/cryptonote_basic.h"
#include "lwe_solver.h"

namespace cryptonote
{
  class miner
  {
  public:
    miner();
    bool generate_lwe_problem(block& bl);
    bool verify_lwe_solution(const block& bl);
  };
}

