#include "DefaultModSetterArithm.h"

ModifierType CDefaultModSetterArithm::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    if (a_param_type == "Immediate")
    {
        return ModifierType::AB;
    }
    if (b_param_type == "Immediate")
    {
        return ModifierType::B;
    }
    return ModifierType::F;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterArithm::clone() const
{
    return std::make_unique<CDefaultModSetterArithm>();
}