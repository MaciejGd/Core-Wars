#include "Player.h"

CPlayer::CPlayer(int id): m_id(id), m_arena(CArena::GetInstance())
{}

bool CPlayer::LoadInitialCode(int &starting_index, int &instructions_amount)
{
    // produce instructions from file choosen for a player
    if (!m_codebuilder.ProduceInstructions(m_file_name))
    {
        // if failed quit immediately
        LOG_ERR("Failed to produce instruction from loaded file {}, aborting"
                , m_file_name);
        return false;
    }
    // obtain amount of instructions loaded
    instructions_amount = m_codebuilder.GetInstructionsAmount();
    // clear tasks queue just to be sure
    m_tasks.clear();
    // load instructions into the core
    starting_index = m_arena.LoadPlayer(m_codebuilder.GetInstructions(), m_id);
    m_tasks.push_back(starting_index);
    return true;
}

bool CPlayer::ExecuteTask(int &modified_cell)
{
    // if m_tasks is empty it means that player lost
    if (m_tasks.empty())
    {
        LOG_ERR("No more tasks left for ");
        return false;
    }
    // get first task and pop it from the queue
    int task = m_tasks.front();
    m_tasks.pop_front();
    // need to keep copy of task as it will be modified in Execute function
    int task_cp = task; 
    LOG_DBG("Executing operation at index {}: {}", task, m_arena[task]->PrintInstruction());
    // execute task on arena
    InstructionResult exe_result = m_arena[task]->Execute(task, modified_cell);
    if (exe_result == InstructionResult::SPLIT)
    {
        // we need to handle SPL instruction separately (creating new process for player)
        m_tasks.push_back((task_cp+1) % ARENA_SIZE);
        m_tasks.push_back(task);
    }
    else if (exe_result == InstructionResult::PASS)
    {
        // if success push task to queue again as it was updated in COperation
        m_tasks.push_back(task);
    }
    else if (exe_result == InstructionResult::FAIL)
    {
        LOG_ERR("Executed wrong instruction process has been killed");
    }
    // check if any processes left for player
    if (m_tasks.empty())
    {
        LOG_ERR("No more tasks left for ");
        return false;
    }
    return true;
}
