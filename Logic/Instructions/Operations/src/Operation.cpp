#include "Operation.h"

std::string ModifierToString(ModifierType modifier)
{
    switch (modifier)
    {
        case A:
            return "A";
        case B:
            return "B";
        case AB:
            return "AB";
        case BA:
            return "BA";
        case F:
            return "F";
        case I:
            return "I";
        case X:
            return "X";
        case DEFAULT:
            return "DEFAULT";
        default:
            return "UnknownModifier";
    }
}

COperation::COperation(): m_modifier(ModifierType::DEFAULT)
{}
