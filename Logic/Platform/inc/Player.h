#pragma once 

#include "Arena.h"
#include "CodeBuilder.h"

#include <deque>
#include <string>


/// Class representing player
/// Loads initial code for the player to the Core, keeps track of player's
/// tasks and executes them using reference to Arena.
class CPlayer {
public:
    CPlayer(int id);

    /// @brief Parse file for player, create instructions and load them into Core
    /// @param starting_index index at which players code should be loaded
    /// @param instructions_amount amount of instructions to be loaded
    /// @param offset program coutner offset to the first instruction
    /// @return boolean indicating result of loading code to core
    bool LoadInitialCode(int &starting_index, int &instructions_amount, int& offset);

    /// @brief Execute operation, at first index of process queue
    /// @param modified_cell update modified_cell if any cell has been modified during execution
    /// @return boolean indicating result of operation
    bool ExecuteTask(int& modified_cell);

    /// @brief Filename setter
    /// @param file_name string_view, file name to be set for player
    inline void SetFileName(std::string_view file_name) { m_file_name = file_name; }

    /// @brief Get first element from processing queue (Program Counter PC)
    /// @return next task to be executed by player
    const inline int GetPC() const { return m_tasks.front(); };  

    /// @brief Check if program has been loaded for player
    /// @return boolean indicating if program has been loaded for player
    const inline bool IsProgramLoaded() const { return m_file_name.empty(); };

    /// @brief Get error message from the process of parsing
    /// @return error message in form of string 
    const std::string GetErrorMessage() const { return m_codebuilder.GetErrorMessage(); };


    /// @brief Get file name that has been set for player
    /// @return file name set for player
    const std::string GetFileName() const { return m_file_name; };
private:
    // player's id
    int m_id;
    // reference to arena will be stored as property, because it will be frequently used
    CArena& m_arena;
    // file name of program launched for a player
    std::string m_file_name;
    // code builder for building instructions from RedCode file
    CCodeBuilder m_codebuilder;
    // processing queue
    std::deque<int> m_tasks;
};