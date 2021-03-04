#include <stdio.h>
#include <stdlib.h>
#include <time.h>


 
// const并未区分出编译期常量和运行期常量
// constexpr限定在了编译期常量

// it must be use pointer's pointer 
// do not know how mush num of resutl it is
// so function arg trans a pointer which did not be allocate memory
int compute(int **ppResult,int &count){

    // int *pResult;
    // pResult = new int[count];

    srand(time(NULL));
    count = rand() % 10;

    *ppResult = new int[count];

    for(int i = 0; i < count;i++){
        (*ppResult)[i]= rand();
    }

}

int main(){

    int *pResult;
    int count;
    count = 0;

    compute(&pResult, count);
}
