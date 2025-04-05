#pragma once

#include <string>
#include <memory>

class CParameter;

///
/// Enumeration type representing all
/// possible modifiers accessible in 
/// RedCode language
///
enum ModifierType {
    A,
    B,
    AB,
    BA,
    I,
    F,
    X,
    DEFAULT
};

/// Enumaration type representing result status
/// of execuing instruction. Possible return codes:
/// - FAIL:  indicates that process executing should be killed
/// - PASS:  indicates correct instruction execution
/// - SPLIT: indicates that new process for executing player should be created
enum InstructionResult {
    FAIL,
    PASS,
    SPLIT
};

/// @brief Function translating modifier type to a proper string 
/// @param modifier type of the modifier to be turned into a string
/// @return string representing modifier type, ex. ".A", ".I", etc
std::string ModifierToString(ModifierType modifier);

///
/// This class defines the structure for all RedCode operations. Each operation
/// has a name and a modifier type, which determines how the operation interacts
/// with its operands. Derived classes must implement the `Execute` function
/// to define the specific behavior of the operation.
///
class COperation {
public:
    COperation(): m_modifier(ModifierType::DEFAULT) {};
    COperation(const COperation& other) = default;

    virtual std::unique_ptr<COperation> clone() const = 0;

    /// @brief Function returning name of the operation, used for debug purposes
    /// @return returns string with operation's name
    const std::string GetOperationName() const { return m_name; };

    /// @brief Modifier type getter
    /// @return type of modifier currently set
    const ModifierType GetModifier() const { return m_modifier; };
    
    /// @brief Modifier type setter 
    /// @param modifier type of modifier to be set
    void SetModifier(ModifierType modifier) { m_modifier = modifier; };

    /// @brief Virtual function, derived classes implements correct behavior of each operation 
    /// @param A_param A parameter of the instruction
    /// @param B_param B parameter of the instruction
    /// @param pc process counter, memory cell player is currently in
    /// @return boolean indicating result of operation, on false player's process will be killed
    virtual InstructionResult Execute(int a_pointer, int b_pointer, int& pc) = 0;
private:
    
protected:
    ModifierType m_modifier;
    std::string m_name="";
};