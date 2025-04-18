#pragma once

#include "Player.h"
#include "Arena.h"

#define CODE_LOADER_TEST_PATH "../tests/code_loading/"

class CodeLoaderTests {
public:
    CodeLoaderTests(): m_arena(CArena::GetInstance()), m_first_player(CPlayer(0)), m_second_player(CPlayer(1)) {}; 

    /// @brief Test of loading program to core
    void RunTestsLoad();

    /// @brief Run a few commands to check if interpreter works correctly
    void RunTestsRunner();


private:
    CArena& m_arena;
    CPlayer m_first_player;
    CPlayer m_second_player;

    void m_ShowArenaLoad(const std::string& file_name, CPlayer& player);
    void m_PrintArena(int pc);
};