#pragma once
#ifndef _BRIDGE_H__
#define _BRIDGE_H__

class CBridge
{
public:
    void SetStartBlockID(int);
    int GetStartBlockID() const;

    void SetEndBlockID(int);
    int GetEndBlockID() const;

    void SetMultiple(double);
    double GetMultiple() const;

    bool operator < (const CBridge) const;
private:
    int m_iStartBlockID;
    int m_iEndBlockID;
    double m_dMultiple;
};

#endif // _BRIDGE_H__