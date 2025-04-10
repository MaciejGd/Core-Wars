#include "DefaultModSetterMOV.h"

ModifierType CDefaultModSetterMOV::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    if (a_param_type == "#")
    {
        return ModifierType::AB;
    }
    if (b_param_type == "#")
    {
        return ModifierType::B;
    }

    return ModifierType::I;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterMOV::clone() const
{
    return std::make_unique<CDefaultModSetterMOV>();
}
