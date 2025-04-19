#include "code_loader.h"

#include <set>
#include <filesystem>

namespace fs = std::filesystem;

void CodeLoaderTests::RunTestsLoad()
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

void CodeLoaderTests::RunTestsRunner()
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
        LOG_ERR("[RUNNING TESTCASE {}]", file_name);
        CPlayer& player = ((i % 2) == 0) ? m_first_player : m_second_player;
        m_ShowArenaLoad(file_name, player);
        // run first 10 instructions
        for (int j = 0; j < 20; j++)
        {
            LOG_ERR("RUNNING {} TASK", j);
            int pc = player.GetPC(); // starting index
            LOG_ERR("ACTUAL Program Counter: {}", pc);
            int modified_cell = -1;
            if (!player.ExecuteTask(modified_cell))
            {
                break;
            }
            m_PrintArena(pc);
        }
        i++;
        if (i >= 1) break;
    }
}

void CodeLoaderTests::m_ShowArenaLoad(const std::string &file_name, CPlayer& player)
{
    m_arena.ClearArena();
    player.SetFileName(file_name);
    int dummy1, dummy2, offset;
    player.LoadInitialCode(dummy1, dummy2, offset);
    int starting_index = player.GetPC();
    // print arena around the first index to check if it has been filled right
    for (int i = starting_index - 30; i < starting_index + 30; i++)
    {
        LOG_WRN("Instr at index {} : {}", i, m_arena[i]->PrintInstruction());
    }
}

void CodeLoaderTests::m_PrintArena(int pc) {
    LOG_ERR("[PRINTING ARENA]");
    for (int i = pc - 30; i < pc + 30; i++)
    {
        LOG_WRN("Instr at index {} : {}", i, m_arena[i]->PrintInstruction());
    }
}   
