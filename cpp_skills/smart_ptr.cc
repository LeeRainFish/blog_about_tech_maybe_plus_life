#include <iostream>
#include <memory>

using namespace std;

// 智能指针 解决 部分内存泄漏问题
//

/*
unique_ptr
shard_ptr
weak_ptr
*/

class A
{
public:
    int i;
    A(int n):i(n) { };
    ~A() { cout << i << " " << "destructed" << endl; }
};

/**
 * 当 std::unique_ptr 离开作用域时, 对象就会被销毁
 *
 */
void *unique_func()
{

}

/*
 * 多个 shared_ptr 对象可以共同托管一个指针 p，
 * 当所有曾经托管p的shared_ptr 对象都解除了对其的托管时
 * 就会执行delete p
 * */
void *shared_func()
{
    shard_ptr<A> sp1(new A(2));
    shard_ptr<A> sp2(sp1);
    shard_ptr<A> sp3;

}

void *weak_func()
{
}


int main()
{

    return 0;
}


