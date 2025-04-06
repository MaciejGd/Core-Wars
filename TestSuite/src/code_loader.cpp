#include "code_loader.h"

#include <set>
#include <filesystem>

namespace fs = std::filesystem;

void CodeLoaderTests::RunTests()
{
    std::string test_path = CODE_LOADER_TEST_PATH;
    // analyze files in alphabetical order so use set
    std::set<std::string> test_files;
    for (const auto& entry : fs::directory_iterator(test_path))
    {
        fs::path test_name = entry.path();
        std::string file_name = test_name.string();
        test_files.insert(file_name);
    }
    int i = 0;
    for (const auto& file_name : test_files)
    {
        CPlayer& player = ((i % 2) == 0) ? m_first_player : m_second_player;
        m_ShowArenaLoad(file_name, player);
        i++;
    }
}

void CodeLoaderTests::m_ShowArenaLoad(const std::string &file_name, CPlayer& player)
{
    m_arena.ClearArena();
    player.SetFileName(file_name);
    player.LoadInitialCode();
    int starting_index = player.GetNextTask();
    // print arena around the first index to check if it has been filled right
    for (int i = starting_index - 30; i < starting_index + 30; i++)
    {
        LOG_WRN("Instr at index {} : {}", i, m_arena[i]->PrintInstruction());
    }
}
