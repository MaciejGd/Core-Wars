#pragma once

#include "Parameter.h"

/// Class representing parameter with address mode of 
/// type "Direct".
class CParameterDirect : public CParameter {
public:
    CParameterDirect() = default;
    CParameterDirect(int val): CParameter(val) {}
    CParameterDirect(const CParameterDirect& other): CParameter(other) {}

    std::unique_ptr<CParameter> clone() const override;

    const std::string Identify() const override { return ""; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "Direct";
};