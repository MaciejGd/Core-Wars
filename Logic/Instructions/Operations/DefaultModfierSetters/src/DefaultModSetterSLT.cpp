#include "DefaultModSetterSLT.h"

ModifierType CDefaultModSetterSLT::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    if (a_param_type == "#")
    {
        return ModifierType::AB;
    }
    return ModifierType::B;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterSLT::clone() const
{
    return std::make_unique<CDefaultModSetterSLT>();
}
