#pragma once

#include "Parameter.h"


class CParameterPostInc : public CParameter {
public:
    CParameterPostInc() = default;
    CParameterPostInc(int val): CParameter(val) {}
    CParameterPostInc(const CParameterPostInc& other): CParameter(other) {}

    std::unique_ptr<CParameter> clone() const override;

    const std::string Identify() const override { return ">"; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "PostInc";
};