#pragma once

#include "Operation.h"

#include <memory>
#include <array>
#include <vector>

#define ARENA_SIZE 8000
#define RW_LIMIT 500

#define PLAYERS_AMOUNT 2 // TODO need reconsideration

class CInstruction;

/// Singleton class holding logic behind arena
/// Arena stores Core instructions in container and
/// provids access to them via [] operator.
class CArena {
public:
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


    /// @brief random access modifier giving access to memory cells 
    /// @param idx index of memmory to be accessed
    /// @return returns reference to unique ptr with instruction stored at idx
    std::unique_ptr<CInstruction>& operator[](int idx);

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