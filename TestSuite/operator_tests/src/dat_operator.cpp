#include "dat_operator.h"
#include "Arena.h"
#include "Instruction.h"
#include "logger.h"

#define STARTING_POINT 100


void DATOperatorTest::RunTests()
{
    m_test();
}


void DATOperatorTest::m_test()
{
    CArena& arena = CArena::GetInstance();
    arena.ClearArena();
    int n_STARTING_POINT = STARTING_POINT;
    if (arena[STARTING_POINT]->Execute(n_STARTING_POINT, modified_cell))
    {
        LOG_FAIL("Executing DAT instruction should return false");
    }
    else 
    {
        LOG_PASS("Executing DAT instruction results in false operation");
    }
}