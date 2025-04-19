#include "Arena.h"
#include "Instruction.h"

#include "logger.h"

#include <random>

CArena CArena::s_instance;


CArena& CArena::GetInstance()
{
    return s_instance;
}

int CArena::Fold(int pointer)
{
    LOG_ERR("In Fold, pointer value: {}", pointer);
    //int result = pointer % ARENA_SIZE;

    int result = ((pointer % RW_LIMIT) + RW_LIMIT) % RW_LIMIT;
    if (result >= RW_LIMIT / 2)
    {
        result -= RW_LIMIT;
    }


    LOG_ERR("Folded to value {}", result);
    return result;
}

std::unique_ptr<CInstruction> &CArena::operator[](int idx)
{
    // wrap index before accessing arena
    int wrapped_idx = ((idx % ARENA_SIZE) + ARENA_SIZE) % ARENA_SIZE;
    LOG_ERR("In ARENA, wrapped index: {}", wrapped_idx);
    return m_arena[wrapped_idx];
}

void CArena::ClearArena()
{
    // overwrite all arena cells with pointer to default instruction
    for (int i = 0; i < m_arena.size(); i++)
    {
        m_arena[i] = CInstruction::CreateDefaultInstruction();
    }
}

int CArena::LoadPlayer(std::vector<std::unique_ptr<CInstruction>> &init_code, int player_id)
{
    // calculate starting point for a player basing on his player id
    int starting_point = m_GenInitialCodePlace(player_id);
    // move instructions from initial vector to core
    for (int i = 0; i < init_code.size(); i++)
    {
        m_arena[starting_point + i] = std::move(init_code[i]);
    }
    // we should clear original vector after moving as it does not own any pointers anymore
    init_code.clear();

    // return starting point so Player can track his program counter
    return starting_point;
}

CArena::CArena()
{
}

int CArena::m_GenInitialCodePlace(int player_id)
{
    // calculate size of chunk for a player
    unsigned int chunk_size = ARENA_SIZE / (PLAYERS_AMOUNT + 1);
    // calculate center around which player's code will be loaded
    unsigned int chunk_center = (chunk_size) * (player_id + 1);
    // use random to generate random number around found center
    std::random_device r;
    std::mt19937 el(r());
    std::uniform_int_distribution<int> dist(chunk_center-m_start_range, chunk_center+m_start_range);
    // return pseudo-random number
    return dist(el);
}