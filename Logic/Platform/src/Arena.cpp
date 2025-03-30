#include "Arena.h"
#include "Instruction.h"

#include "logger.h"

CArena CArena::s_instance;


CArena& CArena::GetInstance()
{
    return s_instance;
}

size_t CArena::Fold(size_t pointer)
{
    size_t result = pointer % ARENA_SIZE;
    if (result > (RW_LIMIT / 2))
    {
        result += ARENA_SIZE - RW_LIMIT;
    }
    return result;
}

std::unique_ptr<CInstruction> &CArena::operator[](size_t idx)
{
    // prevent 
    if (idx >= ARENA_SIZE)
    {
        return m_arena[idx % ARENA_SIZE];
    }
    else if (idx < 0)
    {
        return m_arena[(idx % ARENA_SIZE) + ARENA_SIZE + 1];
    }
    return m_arena[idx];
    // TODO: insert return statement here
}

void CArena::ClearArena()
{
    // over write all arena cells with pointer to default instruction
    for (int i = 0; i < m_arena.size(); i++)
    {
        m_arena[i] = CInstruction::CreateDefaultInstruction();
    }
}

CArena::CArena()
{
}

void CArena::TestPrint()
{
    LOG_WRN("testing arena");
}