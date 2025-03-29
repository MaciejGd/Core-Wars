#pragma once

#include "Operation.h"

#include <string>

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

std::string ModifierToString(ModifierType modifier);

class COperation {
public:
    COperation();

    const std::string GetOperationName() const { return m_name; };

    /// @brief Modifier type getter
    /// @return type of modifier currently set
    const ModifierType GetModifier() const { return m_modifier; };
    
    /// @brief Modifier type setter 
    /// @param modifier type of modifier to be set
    void SetModifier(ModifierType modifier) { m_modifier = modifier; };
private:
    
protected:
    ModifierType m_modifier;
    std::string m_name="";
};