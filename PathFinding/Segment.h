#pragma once
#ifndef _SEGMENT_H__
#define _SEGMENT_H__

class CSegment
{
public:
    void SetID(int);
    int GetID() const;

    void SetType(int);
    int GetType() const;

    void SetWayType(int);
    int GetWayType() const;

    void SetStartNodeID(int);
    int GetStartNodeID() const;

    void SetEndNodeID(int);
    int GetEndNodeID() const;

    void SetVelocityLimit1(double);
    double GetVelocityLimit1() const;

    void SetVelocityLimit2(double);
    double GetVelocityLimit2() const;

    void SetDeadReckonDis(double);
    double GetDeadReckonDis() const;

    void SetObstacle(int);
    int GetObstacle() const;

    void SetGuideType(int);
    int GetGuideType() const;

    void SetDirection(int);
    int GetDirection() const;

    void SetSize(double);
    double GetSize() const;

    void SetSlantAngle(double);
    double GetSlantAngle() const;

    void SetFlexible(int);
    int GetFlexible() const;

    void SetArcDirection(int);
    int GetArcDirection() const;

    void SetCentralX(double);
    double GetCentralX() const;

    void SetCentralY(double);
    double GetCentralY() const;

    void SetRadius(double);
    double GetRadius() const;

    void SetStartAngle(double);
    double GetStartAngle() const;

    void SetEndAngle(double);
    double GetEndAngle() const;

    void SetStartHeading(double);
    double GetStartHeading() const;

    void SetIsReverseEdge(int);
    int GetIsReverseEdge() const;

    void SwapNodes();
    bool operator < (const CSegment Segment) const;
private:
    int     m_iID;             // 路线编号
    int     m_iType;           // 类别
    int     m_iWayType;        // 路线类别（单向/双向）
    int     m_iStartNodeID;    // 起始点
    int     m_iEndNodeID;      // 终点
    double  m_dVelocityLimit1; // 向前速度极限
    double  m_dVelocityLimit2; // 向后速度极限
    double  m_dDeadReckonDis;  // 死区估计距离
    int     m_iObstacle;       // 障碍
    int     m_iGuideType;      // 引导方式
    int     m_iDirection;      // 方向

    double  m_dSize;           // 长度
    double  m_dSlantAngle;     // 倾斜角
    int     m_iFlexible;       // 

    int     m_iArcDirection;   // 弧形方向（逆时针/顺时针）
    double  m_dCentralX;       // 圆心坐标 x
    double  m_dCentralY;       // 圆心坐标 y
    double  m_dRadius;         // 半径
    double  m_dStartAngle;     // 开始角度
    double  m_dEndAngle;       // 结束角度

    double  m_dStartHeading;   // 起始方向
    int     m_iIsReverseEdge;  // 是否是反向边
};

#endif // _SEGMENT_H__