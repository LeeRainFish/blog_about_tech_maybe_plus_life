#include <iostream>

// reference 通常不用于声明变量。
// 而用于参数类型 parameters type
// 和返回类型 return type 描述

void func1(Cls *pobj)
{
    pobj->xxx();
}

void func2(Cls &obj)
{
    obj.xxx();
}

void func3(Cls obj)
{
    obj.xxx();
}

int main(int argc, char **argv)
{

    Cls obj;
    func1(&obj);
    func2(obj);
    func3(obj);

    return 0;
}
