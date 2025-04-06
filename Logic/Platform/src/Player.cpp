#include "Player.h"

CPlayer::CPlayer(int id): m_id(id), m_arena(CArena::GetInstance())
{}

bool CPlayer::LoadInitialCode()
{
    // produce instructions from file choosen for a player
    if (!m_codebuilder.ProduceInstructions(m_file_name))
    {
        // if failed quit immediately
        LOG_ERR("Failed to produce instruction from loaded file {}, aborting"
                , m_file_name);
        return false;
    }
    // clear tasks queue just to be sure
    m_tasks.clear();
    // load instructions into the core
    int starting_task = m_arena.LoadPlayer(m_codebuilder.GetInstructions(), m_id);
    m_tasks.push_back(starting_task);
    return true;
}

bool CPlayer::ExecuteTask()
{
    // if m_tasks is empty it means that player lost
    if (m_tasks.empty())
    {
        return false;
    }
    // get first task and pop it from the queue
    int task = m_tasks.front();
    m_tasks.pop_front();
    // need to keep copy of task as it will be modified in Execute function
    int task_cp = task; 
    // execute task on arena
    if (m_arena[task]->Execute(task) == InstructionResult::SPLIT)
    {
        // we need to handle SPL instruction separately (creating new process for player)
        m_tasks.push_back((task_cp+1) % ARENA_SIZE);
        m_tasks.push_back(task);
    }
    else if (m_arena[task]->Execute(task) == InstructionResult::PASS)
    {
        // if success push task to queue again as it was updated in COperation
        m_tasks.push_back(task);
    }
    return true;
}
