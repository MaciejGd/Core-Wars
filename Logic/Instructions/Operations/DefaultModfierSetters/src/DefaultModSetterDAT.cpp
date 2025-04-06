#include "DefaultModSetterDAT.h"

ModifierType CDefaultModSetterDAT::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    return ModifierType::F;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterDAT::clone() const
{
    return std::unique_ptr<CDefaultModSetterDAT>();
}
