#pragma once

#include "Operation.h"

enum ModifierType {
    A,
    B,
    AB,
    BA,
    I,
    F
};

class COperation {
public:
    COperation() = default;

    const ModifierType GetModifier() const { return m_modifier; }
private:
    ModifierType m_modifier;
};