#pragma once

#include "Operation.h"

#include <memory>
#include <array>

#define ARENA_SIZE 8000
#define RW_LIMIT 500

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
    static size_t Fold(size_t pointer);
    std::unique_ptr<CInstruction>& operator[](size_t idx);

    /// Function that will clear arena, that is fill all 
    /// cells with DAT #0, #0 instructions
    void ClearArena();
private:
    CArena();
    // instance of Arena created on startup, reference to it will be returned from GetInstance
    static CArena s_instance;

    std::array<std::unique_ptr<CInstruction>, ARENA_SIZE> m_arena;

};