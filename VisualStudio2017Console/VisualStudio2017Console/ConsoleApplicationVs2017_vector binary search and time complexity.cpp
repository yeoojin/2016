// ConsoleApplicationVs2017.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

class KData
{
private:
    char*   buffer;
    int     iData;

public:
    static int iConstructor;
    static int iCopyConstructor;
    static int iMoveConstructor;
    static int iDestructor;

public:
    KData(int d_ = 0)
    {
        std::cout << "constructor" << std::endl;
        iData = d_;
        ++iConstructor;
        buffer = new char[100];
    }
    KData(const KData& rhs_)
    {
        std::cout << "copy constructor" << std::endl;
        ++iCopyConstructor;
        iData = rhs_.iData;
        buffer = new char[100];
        memcpy(buffer, rhs_.buffer, sizeof(char) * 100);
    }
    KData(KData&& rhs_)
    {
        std::cout << "move constructor" << std::endl;
        ++iMoveConstructor;
        iData = rhs_.iData;
        buffer = rhs_.buffer;
        rhs_.buffer = nullptr;
    }
    KData& operator=(const KData& rhs_)
    {
        std::cout << "operator=( lvalue ref )" << std::endl;
        ++iCopyConstructor;
        iData = rhs_.iData;
        buffer = new char[100];
        memcpy(buffer, rhs_.buffer, sizeof(char) * 100);
        return *this;
    }
    KData& operator=(KData&& rhs_)
    {
        std::cout << "operator=( rvalue ref )" << std::endl;
        ++iMoveConstructor;
        iData = rhs_.iData;
        buffer = rhs_.buffer;
        rhs_.buffer = nullptr;
        return *this;
    }
    ~KData()
    {
        std::cout << "destructor" << std::endl;
        ++iDestructor;
        delete[] buffer;
        buffer = nullptr;
    }
    void SetInt(int d_)
    {
        iData = d_;
    }
    int GetInt() const { return iData; }

    bool operator==(const KData& rhs_) const
    {
        return iData == rhs_.iData;
    }
    bool operator<(const KData& rhs_) const
    {
        return iData < rhs_.iData;
    }
};

int KData::iConstructor = 0;
int KData::iCopyConstructor = 0;
int KData::iMoveConstructor = 0;
int KData::iDestructor = 0;

template<typename T, typename U>
T myfind(T _first, T _last, const U& _value)
{
    while (_first != _last)
    {
        if (*_first == _value)
            return _first;
        ++_first;
    }
    return _first;
}

int main()
{
    std::vector<KData>  v;
    v.push_back(KData(5));
    v.push_back(KData(4));
    v.push_back(KData(6));
    v.push_back(KData(3));
    v.push_back(KData(7));
    v.push_back(KData(2));
    v.push_back(KData(8));
    v.push_back(KData(1));

    KData d2;
    d2.SetInt(2);

    std::vector<KData>::iterator it = myfind(v.begin(), v.end(), d2);
    if (it != v.end())
    {
        std::cout << it->GetInt() << std::endl;
    }

    it = std::find(v.begin(), v.end(), d2);
    if (it != v.end())
    {
        std::cout << it->GetInt() << std::endl;
    }
    std::sort(v.begin(), v.end());
    bool bFound = std::binary_search( v.begin(), v.end(), d2);
    if ( bFound == true )
    {
        std::cout << d2.GetInt() << std::endl;
    }
    return 0;
}
