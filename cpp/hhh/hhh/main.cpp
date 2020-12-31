//
//  main.cpp
//  hhh
//
//  Created by 李硕 on 12/24/20.
//

#include <bits/stdc++.h>
using namespace std;

struct last_k_numbers{
    int k;
    int sum = 0;
    queue<int> q;
    last_k_numbers(int _k){
        k = _k;
    }
    int next(int new_num){
        q.push(new_num);
        sum += new_num;
        
        if((int)q.size() > k){
            sum -= q.front();
            q.pop();
        }
        return sum;
    }
};

int main(){
    last_k_numbers processor(4);
    
    int num;
    while(cin>>num)
        cout<<processor.next(num)<<"\n";
}
