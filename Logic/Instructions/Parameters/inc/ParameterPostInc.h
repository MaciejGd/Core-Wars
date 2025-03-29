#pragma once

#include "Parameter.h"


class CParameterPostInc : public CParameter {
public:
    CParameterPostInc() = default;
    CParameterPostInc(int val): CParameter(val) {}
    const std::string Identify() const override { return "PostInc"; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "PostInc";
};