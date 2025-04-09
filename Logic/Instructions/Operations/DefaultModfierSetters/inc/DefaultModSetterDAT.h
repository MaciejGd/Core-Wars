#pragma once 

#include "DefaultModSetter.h"


/// Class implementing default modifier deduction for 
/// jump operations: JMP, JMZ, JMN, DJN, SPL
class CDefaultModSetterDAT : public IDefaultModSetter {
public:
    CDefaultModSetterDAT(): IDefaultModSetter() {}

    ModifierType DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type) override;
    
    std::unique_ptr<IDefaultModSetter> clone() const override;

};