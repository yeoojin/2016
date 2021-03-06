#include <stdio.h>
#include <string.h>

// 객체 지향프로그래밍, object oriented programming
class People
{
private:
    char name[20]; // data member
    int age;

public:
    void SetName(const char* n)
    {
        strcpy(name, n);
    }

    void SetAge(int a)
    {
        age = a;
    }

    void Print()
    {
        printf("%s, age=%i\r\n", name, age);
    }
};


void main()
{
    // int i; // int: type, i: variable
    People i; // People: class, i: object객체
    i.SetName("Jintaeks");
    i.SetAge(50);
    i.Print();
}