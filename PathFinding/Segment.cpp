#include "Segment.h"

#include <iostream>

void CSegment::SetID(int id)
{
    m_iID = id;
}

int CSegment::GetID() const
{
    return m_iID;
}

void CSegment::SetType(int type)
{
    m_iType = type;
}

int CSegment::GetType() const
{
    return m_iType;
}

void CSegment::SetWayType(int wayType)
{
    m_iWayType = wayType;
}

int CSegment::GetWayType() const
{
    return m_iWayType;
}

void CSegment::SetStartNodeID(int startNodeID)
{
    m_iStartNodeID = startNodeID;
}

int CSegment::GetStartNodeID() const
{
    return m_iStartNodeID;
}

void CSegment::SetEndNodeID(int endNodeID)
{
    m_iEndNodeID = endNodeID;
}

int CSegment::GetEndNodeID() const
{
    return m_iEndNodeID;
}

void CSegment::SetVelocityLimit1(double velocityLimit1)
{
    m_dVelocityLimit1 = velocityLimit1;
}

double CSegment::GetVelocityLimit1() const
{
    return m_dVelocityLimit1;
}

void CSegment::SetVelocityLimit2(double velocityLimit2)
{
    m_dVelocityLimit2 = velocityLimit2;
}

double CSegment::GetVelocityLimit2() const
{
    return m_dVelocityLimit2;
}

void CSegment::SetDeadReckonDis(double deadReckonDis)
{
    m_dDeadReckonDis = deadReckonDis;
}

double CSegment::GetDeadReckonDis() const
{
    return m_dDeadReckonDis;
}

void CSegment::SetObstacle(int obstacle)
{
    m_iObstacle = obstacle;
}

int CSegment::GetObstacle() const
{
    return m_iObstacle;
}

void CSegment::SetGuideType(int guideType)
{
    m_iGuideType = guideType;
}

int CSegment::GetGuideType() const
{
    return m_iGuideType;
}

void CSegment::SetDirection(int direction)
{
    m_iDirection = direction;
}

int CSegment::GetDirection() const
{
    return m_iDirection;
}

void CSegment::SetSize(double size)
{
    m_dSize = size;
}

double CSegment::GetSize() const
{
    return m_dSize;
}

void CSegment::SetSlantAngle(double slantAngle)
{
    m_dSlantAngle = slantAngle;
}

double CSegment::GetSlantAngle() const
{
    return m_dSlantAngle;
}

void CSegment::SetFlexible(int flexible)
{
    m_iFlexible = flexible;
}

int CSegment::GetFlexible() const
{
    return m_iFlexible;
}

void CSegment::SetArcDirection(int arcDirection)
{
    m_iArcDirection = arcDirection;
}

int CSegment::GetArcDirection() const
{
    return m_iArcDirection;
}

void CSegment::SetCentralX(double centralX)
{
    m_dCentralX = centralX;
}

double CSegment::GetCentralX() const
{
    return m_dCentralX;
}

void CSegment::SetCentralY(double centralY)
{
    m_dCentralY = centralY;
}

double CSegment::GetCentralY() const
{
    return m_dCentralY;
}

void CSegment::SetRadius(double radius)
{
    m_dRadius = radius;
}

double CSegment::GetRadius() const
{
    return m_dRadius;
}

void CSegment::SetStartAngle(double startAngle)
{
    m_dStartAngle = startAngle;
}

double CSegment::GetStartAngle() const
{
    return m_dStartAngle;
}

void CSegment::SetEndAngle(double endAngle)
{
    m_dEndAngle = endAngle;
}

double CSegment::GetEndAngle() const
{
    return m_dEndAngle;
}

void CSegment::SetStartHeading(double startHeading)
{
    m_dStartHeading = startHeading;
}

double CSegment::GetStartHeading() const
{
    return m_dStartHeading;
}

void CSegment::SetIsReverseEdge(int isReverseEdge)
{
    m_iIsReverseEdge = isReverseEdge;
}

int CSegment::GetIsReverseEdge() const
{
    return m_iIsReverseEdge;
}

void CSegment::SwapNodes()
{
    std::swap(m_iStartNodeID, m_iEndNodeID);
}

bool CSegment::operator < (const CSegment Segment) const
{
    if (m_iStartNodeID != Segment.m_iStartNodeID)
    {
        return m_iStartNodeID < Segment.m_iStartNodeID;
    }
    return m_iEndNodeID < Segment.m_iEndNodeID;
}
