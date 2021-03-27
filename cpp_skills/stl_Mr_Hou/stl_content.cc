#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <array>

// red_black_tree
#include <set>
#include <map>

// hash
#include <unordered_set>
#include <unordered_map>



void iter_test()
{
    vector<int> v;

    // before c11
    vector<int>::iterator it = v.begin();
    for(;it != b.end(); it++){

    }
    // end poiter not in container
    //
    
    // after c11
    for(auto it : v){

    }

    for(auto &it : v){

    }

}



int main()
{


    return 0;
}
