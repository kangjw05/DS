#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#define INF 1000000000.0

using namespace std;
typedef pair<double, double> Node;

vector<Node> tree;
vector<pair<int, double>> arr;

Node merge(const Node& left, const Node& right) {
    return {min(left.first, right.first), max(left.second, right.second)};
} 

Node init(int idx, int s, int e) {
    if (s==e) return tree[idx] = {arr[s].second, arr[s].second};

    int mid = (s+e)/2;
    Node left = init(2*idx, s, mid);
    Node right = init(2*idx+1, mid+1, e);
    return tree[idx] = merge(left, right);
}

Node query(int idx, int s, int e, int l, int r) {
    if (e<l || r<s) return {INF,-INF};
    if (l<=s && e<=r) return tree[idx];

    int mid = (s+e)/2;
    Node left = query(2*idx, s, mid, l, r);
    Node right = query(2*idx+1, mid+1, e, l, r);
    return merge(left, right);
}


int main() {    
    
    ios_base::sync_with_stdio(false);

    ifstream file("Pitcoin_sample.txt");
    int N;
    file >> N;
    int time;
    double price;
    for (int i=0; i<N; i++) {
        file >> time >> price;
        arr.push_back({time, price});
    }
    
    file.close();

    tree.resize(4*N);

    init(1,0,N-1);

    int n, start, end;
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> start >> end;    

        auto it_start = upper_bound(arr.begin(), arr.end(), make_pair(start, INF));
        int start_idx = distance(arr.begin(), it_start)-1;
        auto it_end = upper_bound(arr.begin(), arr.end(), make_pair(end, INF));
        int end_idx = distance(arr.begin(), it_end)-1;

        Node result = query(1,0,N-1,start_idx,end_idx);

        cout << result.first << " " << result.second << endl;

    }
    
    
    return 0;
}

