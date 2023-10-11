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
    double  m_dX;      // ¿é X ×ø±ê
    double  m_dY;      // ¿é Y ×ø±ê
    int     m_iID;     // ¿é±àºÅ
    int     m_iCount;  // µãÊý
};

#endif // _BLOCK_H__