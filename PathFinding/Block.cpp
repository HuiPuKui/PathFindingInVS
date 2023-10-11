#include "Block.h"

void CBlock::SetX(double x)
{
    m_dX = x;
}

double CBlock::GetX() const
{
    return m_dX;
}

void CBlock::SetY(double y)
{
    m_dY = y;
}

double CBlock::GetY() const
{
    return m_dY;
}

void CBlock::SetID(int id)
{
    m_iID = id;
}

int CBlock::GetID() const
{
    return m_iID;
}

void CBlock::SetCount(int count)
{
    m_iCount = count;
}

int CBlock::GetCount() const
{
    return m_iCount;
}