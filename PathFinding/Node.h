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
    int     m_iID;                 // 点的编号
    int     m_iNodeType;           // 点的类型
    double  m_dX;                  // 点 X 坐标
    double  m_dY;                  // 点 Y 坐标
    double  m_dHeading;            // 朝向
    int     m_iObstacle;           // 障碍
    double  m_dCheckMarkDistance;  // 检查标记距离
    double  m_dCheckMarkVelocity;  // 检查标记速度
    int     m_iRFID;               // 射频识别
    int     m_iWhichBlock;
};

#endif // _NODE_H__