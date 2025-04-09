#pragma once

#include "Operation.h"

#include <memory>
#include <array>
#include <vector>

#define ARENA_SIZE 8000
#define RW_LIMIT 1000

#define PLAYERS_AMOUNT 2 // TODO need reconsideration

class CInstruction;

/// @brief Singleton class holding logic behind arena
/// 
/// Many other classes will reference Arena, so retrieving pointer to instance
/// without caring about passing reference or pointer in function calls will 
/// be big plus of using Singleton pattern.
///
/// Another plus of using Singleton in this case is that constructor of Arena shouldn't
/// be called explicitly, only one instance of arena should be created during program execution
class CArena {
public:
    void TestPrint();

    // we should delete copy constructor, move constructor, copy and move assignements operators
    CArena(const CArena& arena) = delete; 
    CArena(CArena && arena) = delete;
    CArena& operator=(const CArena& arena) = delete;
    CArena& operator=(CArena&& arena) = delete;

    static CArena& GetInstance();

    /// @brief Function to fold addresses going out of limit set
    /// @param pointer pointer to fold to desired range
    /// @param limit limit of the range
    /// @return size_t indicating position after folding
    static int Fold(int pointer);
    std::unique_ptr<CInstruction>& operator[](size_t idx);

    /// Function that will clear arena, that is fill all 
    /// cells with DAT #0, #0 instructions
    void ClearArena();

    /// @brief Function for loading Player's initial code to arena
    /// @param init_code vector of starting instructions to be loaded to Core
    /// @param player_id id of the player that instructions belong to
    /// @return starting program counter for a player
    int LoadPlayer(std::vector<std::unique_ptr<CInstruction>>& init_code, int player_id);
private:
    CArena();
    // instance of Arena created on startup, reference to it will be returned from GetInstance
    static CArena s_instance;

    std::array<std::unique_ptr<CInstruction>, ARENA_SIZE> m_arena;

    int m_GenInitialCodePlace(int player_id);

    const int m_start_range = 500;
};