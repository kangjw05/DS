#include <bits/stdc++.h>

using namespace std;
int Comp, D;

int main() {
    char c;
    while(cin >> c){
        c=='{' ? Comp+=++D:(c=='}' ? D--:0);
    }
    cout << Comp;

    return 0;
}