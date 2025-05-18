#include <bits/stdc++.h>
using namespace std;

int main() {
    pair<int, int> p1(1, 2);  // ✅ Correct
    pair<int, int> p2(2, 1);
    pair<int, int> p3(1, 2);

    cout << p1.first << " " << p1.second << endl; 
    return 0;
}