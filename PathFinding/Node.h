#pragma once
#ifndef _NODE_H__
#define _NODE_H__

class CNode
{
public:
    void SetID(int);
    int GetID() const;

    void SetNodeType(int);
    int GetNodeType() const;

    void SetX(double);
    double GetX() const;

    void SetY(double);
    double GetY() const;

    void SetHeading(double);
    double GetHeading() const;

    void SetObstacle(int);
    int GetObstacle() const;

    void SetCheckMarkDistance(double);
    double GetCheckMarkDistance() const;

    void SetCheckMarkVelocity(double);
    double GetCheckMarkVelocity() const;

    void SetRFID(int);
    int GetRFID() const;

    void SetWhichBlock(int);
    int GetWhichBlock() const;

    bool operator < (const CNode) const;
private:
    int     m_iID;                 // ��ı��
    int     m_iNodeType;           // �������
    double  m_dX;                  // �� X ����
    double  m_dY;                  // �� Y ����
    double  m_dHeading;            // ����
    int     m_iObstacle;           // �ϰ�
    double  m_dCheckMarkDistance;  // ����Ǿ���
    double  m_dCheckMarkVelocity;  // ������ٶ�
    int     m_iRFID;               // ��Ƶʶ��
    int     m_iWhichBlock;
};

#endif // _NODE_H__