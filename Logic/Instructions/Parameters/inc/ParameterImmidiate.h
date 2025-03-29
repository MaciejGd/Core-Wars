#pragma once

#include "Parameter.h"


class CParameterImmidiate : public CParameter {
public:
    CParameterImmidiate() = default;
    CParameterImmidiate(int val): CParameter(val) {}
    const std::string Identify() const override { return "Immidiate"; };

    void EvaluateParameter(int pc) override;
protected:
    const std::string m_id = "Immidiate";
};