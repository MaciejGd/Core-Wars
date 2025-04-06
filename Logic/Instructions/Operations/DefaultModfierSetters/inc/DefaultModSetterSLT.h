#pragma once 

#include "DefaultModSetter.h"


/// Class implementing default modifier deduction for 
/// operation SLT
class CDefaultModSetterSLT : public IDefaultModSetter {
public:
    CDefaultModSetterSLT(): IDefaultModSetter() {}
    CDefaultModSetterSLT(const CDefaultModSetterSLT& other): IDefaultModSetter(other) {};
    ModifierType DeduceDefaultModSetter(std::string_view a_param_type, std::string_view b_param_type) override;
    std::unique_ptr<IDefaultModSetter> clone() const override;

};