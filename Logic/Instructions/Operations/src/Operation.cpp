#include "Operation.h"
#include "logger.h"

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

COperation::COperation(const COperation &other)
{
    // need to perform copy of DefaultModifierSetter
    m_modifier = other.m_modifier;
    m_name = other.m_name;
    m_def_modifier = other.m_def_modifier->clone();
}

void COperation::DeduceDefaultModifier(std::string_view a_param_type, std::string_view b_param_type)
{
    // deduce default modifier if no modifier has been specified during code parsing
    if (m_modifier == ModifierType::DEFAULT)
    {
        m_modifier = m_def_modifier->DeduceDefaultModSetter(a_param_type, b_param_type);
        LOG_DBG("Swtiched default modifier to {}", ModifierToString(m_modifier));
    }
}