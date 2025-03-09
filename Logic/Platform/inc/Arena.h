#pragma once

#include <memory>
#include <vector>
// what should arena do???

#include "Operation.h"

/// @brief Class holding logic behind arena
class CArena {
public:
    CArena();
    void TestPrint();

    void InitPlayers();
private:
    static const int MAX_TAPE_LEN = 8000; // len of turing tape arena
    std::vector<std::unique_ptr<COperation>> arena;
};