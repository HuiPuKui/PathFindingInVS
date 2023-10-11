#include "Bridge.h"

void CBridge::SetStartBlockID(int startBlockID)
{
    m_iStartBlockID = startBlockID;
}

int CBridge::GetStartBlockID() const
{
    return m_iStartBlockID;
}

void CBridge::SetEndBlockID(int endBlockID)
{
    m_iEndBlockID = endBlockID;
}

int CBridge::GetEndBlockID() const
{
    return m_iEndBlockID;
}

void CBridge::SetMultiple(double multiple)
{
    m_dMultiple = multiple;
}

double CBridge::GetMultiple() const
{
    return m_dMultiple;
}

bool CBridge::operator < (const CBridge Bridge) const
{
    if (m_iStartBlockID != Bridge.m_iStartBlockID)
    {
        return m_iStartBlockID < Bridge.m_iStartBlockID;
    }
    if (m_iEndBlockID != Bridge.m_iEndBlockID)
    {
        return m_iEndBlockID < Bridge.m_iEndBlockID;
    }
    return m_dMultiple > Bridge.m_dMultiple;
}