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
    int     m_iID;             // ·�߱��
    int     m_iType;           // ���
    int     m_iWayType;        // ·����𣨵���/˫��
    int     m_iStartNodeID;    // ��ʼ��
    int     m_iEndNodeID;      // �յ�
    double  m_dVelocityLimit1; // ��ǰ�ٶȼ���
    double  m_dVelocityLimit2; // ����ٶȼ���
    double  m_dDeadReckonDis;  // �������ƾ���
    int     m_iObstacle;       // �ϰ�
    int     m_iGuideType;      // ������ʽ
    int     m_iDirection;      // ����

    double  m_dSize;           // ����
    double  m_dSlantAngle;     // ��б��
    int     m_iFlexible;       // 

    int     m_iArcDirection;   // ���η�����ʱ��/˳ʱ�룩
    double  m_dCentralX;       // Բ������ x
    double  m_dCentralY;       // Բ������ y
    double  m_dRadius;         // �뾶
    double  m_dStartAngle;     // ��ʼ�Ƕ�
    double  m_dEndAngle;       // �����Ƕ�

    double  m_dStartHeading;   // ��ʼ����
    int     m_iIsReverseEdge;  // �Ƿ��Ƿ����
};

#endif // _SEGMENT_H__