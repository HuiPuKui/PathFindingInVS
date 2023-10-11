#pragma once
#ifndef _BLOCK_H__
#define _BLOCK_H__

class CBlock
{
public:
    void SetX(double);
    double GetX() const;

    void SetY(double);
    double GetY() const;

    void SetID(int);
    int GetID() const;

    void SetCount(int);
    int GetCount() const;
private:
    double  m_dX;      // �� X ����
    double  m_dY;      // �� Y ����
    int     m_iID;     // ����
    int     m_iCount;  // ����
};

#endif // _BLOCK_H__