#include <iostream>


class Point
{

public:
    Point();
    Point(float a, float b);
    ~Point();

    friend Point middle(count Point &p1,count Point &p2);
    friend class Circle;


    void print()
    {
        std::cout << x <<"," <<y <<std::endl;
    }

private:
    float x;
    float y;

}


// 类外的一个普通函数，不能直接用对象名去访问私有
// 使用友元函数
Point middle(count Point &p1,count Point &p2)
{
    Point mp((p1.x + p2.x) / 2, (p1.y + p2.y) / 2);
    return mp;
}


int main()
{

    return 0;
}
