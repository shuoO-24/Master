//
//  main.cpp
//  test
//
//  Created by 李硕 on 12/21/20.
//

#include <bits/stdc++.h>

using namespace std;

int main(){
    int a, b, c, d, M, V;
    cin >> a >> b >> c >> d;
    M = max((3*a)/10, a-(c/250)*c);
    V = max((3*b)/10, b-(d/250)*d);
    if (M>V) cout << "Misha" << endl;
    if (M<V) cout << "Vasya" << endl;
    if (M==V) cout << "Tie" << endl;
}
