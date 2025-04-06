#include "DefaultModSetterJump.h"

ModifierType CDefaultModSetterJump::DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type)
{
    // default modifer for all jump operations: JMP,JMZ,JMN,DJN,SPL will be B
    return ModifierType::B;
}

std::unique_ptr<IDefaultModSetter> CDefaultModSetterJump::clone() const
{
    return std::unique_ptr<CDefaultModSetterJump>();
}
