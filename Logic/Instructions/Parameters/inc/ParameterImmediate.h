#pragma once

#include "Parameter.h"


class CParameterImmediate : public CParameter {
public:
    CParameterImmediate() = default;
    CParameterImmediate(int val): CParameter(val) {}
    CParameterImmediate(const CParameterImmediate& other): CParameter(other) {}

    std::unique_ptr<CParameter> clone() const override;

    const std::string Identify() const override { return "#"; };

    void EvaluateParameter(int pc) override;
protected:
    const std::string m_id = "Immediate";
};