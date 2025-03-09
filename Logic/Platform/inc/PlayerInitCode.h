#pragma once

#include <vector>
#include <memory>

#include "Operation.h"

class CPlayerInitCode {
public:
    CPlayerInitCode();
    void AddInstruction(std::unique_ptr<COperation> op);
private:
    std::vector<std::unique_ptr<COperation>> m_code;
protected:



};