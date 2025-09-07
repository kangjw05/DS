#include <bits/stdc++.h>
using namespace std;

#define PB push_back
#define F first
#define S second

using P = pair<int, int>; // P: Point (x, y)
struct I {                 // I: Info
    P p;                   // p: point
    P d;                   // d: direction
    int dist;              // distance
};

// pair operator overloading
P operator+(P a, P b) { return {a.F + b.F, a.S + b.S}; }
P operator*(P a, int b) { return {a.F * b, a.S * b}; }

// solve: get_point at time t
// v: pointer Infos , t: time 
P solve(vector<I>& v, int t) { 
    for (size_t i = 0; i < v.size() - 1; ++i) {
        if (t < v[i+1].dist) return v[i].p + (v[i].d * (t - v[i].dist));
    }
    return v.back().p + (v.back().d * (t - v.back().dist));
}

int main() {
    int k; // number of points
    cin >> k;
    vector<P> p(k); // points
    for (int i = 0; i < k; ++i) cin >> p[i].F >> p[i].S;

    vector<I> v; // pointer Infos
    int len = 0; // length
    for (int i = 0; i < k; ++i) {
        P a = p[i], b = p[(i + 1) % k];
        int dx = b.F - a.F, dy = b.S - a.S;
        P dir;
        if (dx) dir = {(dx > 0) - (dx < 0), 0};
        else dir = {0, (dy > 0) - (dy < 0)};
        
        v.PB({a, dir, len});
        len += abs(dx) + abs(dy);
    }

    for (int i = 0; i < 5; ++i) {
        int t; // t: time 
        cin >> t;
        P res = solve(v, len ? t % len : 0); // res: result psition
        cout << res.F << " " << res.S << "\n";
    }
    return 0;
}