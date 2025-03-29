#pragma once

#include "Parameter.h"


class CParameterPreDecr : public CParameter {
public:
    CParameterPreDecr() = default;
    CParameterPreDecr(int val): CParameter(val) {}
    const std::string Identify() const override { return "PreDecr"; };

    void EvaluateParameter(int pc) override;
private:

protected:
    const std::string m_id = "PreDecr";
};