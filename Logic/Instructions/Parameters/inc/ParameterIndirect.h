#pragma once

#include "Parameter.h"

/// Class representing parameter with address mode of 
/// type "Indirect".
class CParameterIndirect : public CParameter {
public:
    CParameterIndirect() = default;
    CParameterIndirect(int val): CParameter(val) {}
    CParameterIndirect(const CParameterIndirect& other): CParameter(other) {}

    std::unique_ptr<CParameter> clone() const override;

    const std::string Identify() const override { return "@"; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "Indirect";
};