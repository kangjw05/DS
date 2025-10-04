#include <bits/stdc++.h>
using namespace std;
#define ALL(x) (x).begin(),(x).end()

struct S {
    string n;
    int att, sum, low, high, full;

    // constructor
    S(string n, vector<int> &v) : n(n){
        att = count_if(ALL(v),[](int x){return x;});
        sum = accumulate(ALL(v),0);
        low = 101; 
        bool submitted = false;
        for (int score : v) {
            if (score > 0) {
                low = min(low, score);
                submitted = true;
            }
        }
        if (!submitted) { 
            low = 0;
        }
        high = *max_element(ALL(v));
        full = count(ALL(v), 100);
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, k;
    cin >> N >> k;
    vector<int> seq(5); 
    for(int &i : seq) cin >> i;
    vector<S> A; 
    A.reserve(N);
    while(N--){
        string n;
        cin >> n;
        vector<int> v(k); 
        for(int &i : v) cin >> i;
        A.emplace_back(n, v);
    }

    // Multiple Conditions Alignment Sort
    sort(ALL(A), [&](auto &a, auto &b){
        for(int x : seq){
            int va = 0, vb = 0;
            if(x == 1) va = a.att, vb = b.att;
            if(x == 2) va = a.sum, vb = b.sum;
            if(x == 3) va = a.low, vb = b.low;
            if(x == 4) va = a.high, vb = b.high;
            if(x == 5) va = a.full, vb = b.full;
            if(va != vb) return va > vb;
        }
        return a.n < b.n;
    });

    for(auto &s : A) cout << s.n << "\n";
}
