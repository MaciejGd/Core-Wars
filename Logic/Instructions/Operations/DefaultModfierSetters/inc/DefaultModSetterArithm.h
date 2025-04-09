#pragma once

#include "DefaultModSetter.h"


/// Class implementing default modifier deduction for 
/// arithmetic operations ADD, SUB, MUL, DIV and MOD
class CDefaultModSetterArithm : public IDefaultModSetter {
public:
    CDefaultModSetterArithm(): IDefaultModSetter() {}

    ModifierType DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type) override;

    std::unique_ptr<IDefaultModSetter> clone() const override;
};