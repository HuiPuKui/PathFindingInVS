#include "Node.h"

void CNode::SetID(int id)
{
    m_iID = id;
}

int CNode::GetID() const
{
    return m_iID;
}

void CNode::SetNodeType(int nodeType)
{
    m_iNodeType = nodeType;
}

int CNode::GetNodeType() const
{
    return m_iNodeType;
}

void CNode::SetX(double x)
{
    m_dX = x;
}

double CNode::GetX() const
{
    return m_dX;
}

void CNode::SetY(double y)
{
    m_dY = y;
}

double CNode::GetY() const
{
    return m_dY;
}

void CNode::SetHeading(double heading)
{
    m_dHeading = heading;
}

double CNode::GetHeading() const
{
    return m_dHeading;
}

void CNode::SetObstacle(int obstacle)
{
    m_iObstacle = obstacle;
}

int CNode::GetObstacle() const
{
    return m_iObstacle;
}

void CNode::SetCheckMarkDistance(double checkMarkDistance)
{
    m_dCheckMarkDistance = checkMarkDistance;
}

double CNode::GetCheckMarkDistance() const
{
    return m_dCheckMarkDistance;
}

void CNode::SetCheckMarkVelocity(double checkMarkVelocity)
{
    m_dCheckMarkVelocity = checkMarkVelocity;
}

double CNode::GetCheckMarkVelocity() const
{
    return m_dCheckMarkVelocity;
}

void CNode::SetRFID(int rfid)
{
    m_iRFID = rfid;
}

int CNode::GetRFID() const
{
    return m_iRFID;
}

bool CNode::operator < (const CNode Node) const
{
    return m_iID < Node.m_iID;
}

void CNode::SetWhichBlock(int whichBlock)
{
    m_iWhichBlock = whichBlock;
}

int CNode::GetWhichBlock() const
{
    return m_iWhichBlock;
}