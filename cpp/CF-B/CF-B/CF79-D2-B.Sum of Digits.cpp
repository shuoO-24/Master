//
//  main.cpp
//  CF-B
//
//  Created by 李硕 on 12/31/20.
//
#include <iostream>
#include <string>

using namespace std;


int main(){
    string str;
    cin >> str;
    int sum = 0;
    
    for (int i = 0; i < str.length(); i ++){
        sum += str[i] - '0';
    }
    
    
    while(sum>9){
        string s = to_string(sum);
        sum = 0;
        for (int j = 0; j < s.length(); j ++){
            sum += s[j] - '0';
        }
        if (sum <= 9 && sum > 0) break;
    }
    cout << sum << endl;
}
