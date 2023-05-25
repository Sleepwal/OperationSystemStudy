//
// Created by manson on 2023/5/25.
//

#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

int f(int n) {
    if (n <= 1) return 1;
    return n + f(n - 1);
}

int sum1 = 0;

void f1(int n) {
    stack<int> stack;
    stack.push(n);
    while(!stack.empty()) {
        auto s = stack.top();
        stack.pop();
        if(s <= 1)  { //base case
            sum1 += 1;
            break;
        }

        sum1 += s;
        stack.push(s - 1);
    }
}

int main() {
    int res = f(5);
    f1(5);
    cout << res << endl;
    cout << sum1 << endl;

    return 0;
}
