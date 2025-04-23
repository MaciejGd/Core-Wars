#pragma once

#include "Parameter.h"

/// Class representing parameter with address mode of 
/// type "PreDecrementing".
class CParameterPreDecr : public CParameter {
public:
    CParameterPreDecr() = default;
    CParameterPreDecr(int val): CParameter(val) {}
    CParameterPreDecr(const CParameterPreDecr& other): CParameter(other) {}

    std::unique_ptr<CParameter> clone() const override;

    const std::string Identify() const override { return "<"; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "PreDecr";
};