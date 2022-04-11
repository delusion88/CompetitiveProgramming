#include <bits/stdc++.h>
using namespace std;
mt19937 m((uint_fast32_t)clock()); 
int randint (int a, int b) {
    int x = 1;
    for (int i = 0; i < 10000; i++)
        x %= 10;
    uniform_int_distribution<int> uid(a, b);
    return uid(m);
}
int main () {
    
}