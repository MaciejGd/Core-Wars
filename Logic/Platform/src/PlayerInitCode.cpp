#include "PlayerInitCode.h"


CPlayerInitCode::CPlayerInitCode()
{

}

void CPlayerInitCode::AddInstruction(std::unique_ptr<COperation> op)
{
    m_code.push_back(std::move(op));
}
