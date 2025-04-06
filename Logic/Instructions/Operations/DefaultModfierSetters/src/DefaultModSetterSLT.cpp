#include "DefaultModSetterSLT.h"

ModifierType CDefaultModSetterSLT::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    if (a_param_type == "Immediate")
    {
        return ModifierType::AB;
    }
    return ModifierType::B;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterSLT::clone() const
{
    return std::unique_ptr<CDefaultModSetterSLT>();
}
