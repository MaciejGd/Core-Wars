#pragma once 

#include "Arena.h"
#include "CodeBuilder.h"
#include "PlayerHead.h"

#include <deque>
#include <string>


/// Class representing player
/// Loads initial code for the player to the Core, keeps track of player's
/// tasks and executes them using reference to Arena.
class CPlayer {
public:
    CPlayer(int id);

    bool LoadInitialCode(int &starting_index, int &instructions_amount);

    bool ExecuteTask();

    inline void SetFileName(std::string_view file_name) { m_file_name = file_name; }

    // debug
    const int GetPC() const { return m_tasks.front(); };  
private:
    // player's id
    int m_id;
    // reference to arena will be stored as property, because it will be frequently used
    CArena& m_arena;
    // file name of program launched for a player
    std::string m_file_name;

    CCodeBuilder m_codebuilder;
    std::deque<int> m_tasks;
};