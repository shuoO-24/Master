//
//  main.cpp
//  Udemy C++ Course
//
//  Created by 李硕 on 12/31/20.
//

#include <iostream>
#include <vector>
using namespace std;

void print(vector<vector<int> > &v2d) {
    for (auto &row : v2d)        // auto = vector<int<
    {
        for (auto &col : row)    // auto = int
            cout << col << " ";
        cout << "\n";
    }
    cout << "\n\n";
}

void test2() {
    // 2D Array using vector
    // (5, 7) 2d array
    vector<int> row(5, 1);    // 5 numbers, each is 1

    // 3 rows: each is 5 values of 1
    vector<vector<int> > v2d(3, row);

    //print(v2d);

    int rows = (int)v2d.size();
    int cols = (int)v2d[0].size();    // 3 5
    
    cout << cols << endl;

    v2d[0][0] = 9;
    v2d[1].push_back(5);
    v2d[1].push_back(6);
    v2d[2].erase(v2d[2].begin());

    //print(v2d);
}

int main() {
    test2();
    return 0;
}
