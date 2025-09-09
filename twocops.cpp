#include <bits/stdc++.h>
using namespace std;

#define PAIR pair<int,int>
#define REP(i,n) for(int i=0;i<(n);++i)
#define ll long long

// idea: 1. simulate two cops' movement without collision.
// 2. if they meet odd times, swap their positions.

struct Info {  // base on c1
    PAIR p;   // start point of segment
    PAIR d;   // direction of segment
    ll   dist;  // distance from c1
};

static inline PAIR operator+(PAIR a, PAIR b){ return {a.first + b.first, a.second + b.second}; }
static inline PAIR operator*(PAIR a, ll k){ return {a.first * (int)k, a.second * (int)k}; }

// s = moved distance, L = total length
PAIR posAt(const vector<Info>& info, ll s, ll L){
    if(L > 0) s %= L;      // normalize
    if(s < 0) s += L;
    int n = (int)info.size();

    // find segment with binary search
    int lo = 0, hi = n;
    while(lo + 1 < hi){
        int mid = (lo + hi) >> 1;
        if(info[mid].dist <= s) lo = mid;
        else hi = mid;
    }
    ll off = s - info[lo].dist;
    return info[lo].p + info[lo].d * off;
}

int main(){
    int n;   // points number
    cin >> n;
    vector<PAIR> Points(n);  // points
    REP(i,n) cin >> Points[i].first >> Points[i].second;

    // store info of each points
    vector<Info> info; info.reserve(n);
    ll L=0;  // length
    REP(i,n){
        PAIR a = Points[i], b = Points[(i+1) % n];
        int dx = b.first - a.first, dy = b.second - a.second;
        PAIR dir = {(dx == 0 ? 0 : (dx > 0 ? 1 : -1)), (dy == 0 ? 0 : (dy > 0 ? 1 : -1))};
        info.push_back({a, dir, L});
        L += llabs((ll)dx) + llabs((ll)dy);
    }

    ll D = info[n/2 - 1].dist;  // distance between c1 and c2

    ll t;  // time
    cin >> t;

    // directions
    // c1: clockwise / c2: counter-clockwise
    ll s1 = t % L;
    ll s2 = (D - (t % L)) % L;  // -t because counter-clockwise
    if(s2 < 0) s2 += L;         // normalize to [0, L)

    // position at time t without collision
    PAIR g1 = posAt(info, s1, L);
    PAIR g2 = posAt(info, s2, L);

    // meeting count
    ll meet = 0;
    if(2*t >= D) meet = (2*t - D) / L + 1;  // +1 for first meet
    PAIR c1 = (meet % 2) ? g2 : g1; // meeting count odd -> swap
    PAIR c2 = (meet % 2) ? g1 : g2;

    cout << c1.first << ' ' << c1.second << '\n';
    cout << c2.first << ' ' << c2.second << '\n';
    return 0;
}
