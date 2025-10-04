#include <bits/stdc++.h>
using namespace std;

int N, k;
vector<vector<int>> Waitroom;

void split_if_full(int idx) {
    if ((int)Waitroom[idx].size() == 2 * k) {
        // duplicate right part
        vector<int> right(Waitroom[idx].begin() + k, Waitroom[idx].end());
        // remove right part from original
        Waitroom[idx].erase(Waitroom[idx].begin() + k, Waitroom[idx].end());
        // insert new chair
        Waitroom.insert(Waitroom.begin() + idx + 1, move(right));
    }
}

void insert_p(int p) {
    if (Waitroom.empty()) {
        Waitroom.push_back({p});
        return;
    }

    int idx = 0;
    // find the block that p can be inserted
    while (idx < (int)Waitroom.size() && Waitroom[idx].front() < p) idx++;

    if (idx == 0) {
        // if p is the smallest
        auto &chair = Waitroom[0];
        auto it = lower_bound(chair.begin(), chair.end(), p);
        chair.insert(it, p);
        split_if_full(0);
    } else if (idx == (int)Waitroom.size()) {
        // if p is the largest
        auto &chair = Waitroom.back();
        auto it = lower_bound(chair.begin(), chair.end(), p);
        chair.insert(it, p);
        split_if_full((int)Waitroom.size()-1);
    } else {
        // if p is in the middle
        auto &chair = Waitroom[idx-1];
        auto it = lower_bound(chair.begin(), chair.end(), p);
        chair.insert(it, p);
        split_if_full(idx-1);
    }
}

void erase_p(int p) {
    for (int i = 0; i < (int)Waitroom.size(); ++i) {
        auto &chair = Waitroom[i];
        auto it = lower_bound(chair.begin(), chair.end(), p);
        if (it != chair.end() && *it == p) {
            chair.erase(it);
            // if chair is empty, remove it
            if (chair.empty()) {
                Waitroom.erase(Waitroom.begin() + i);
            }
            return;
        }
    }
}

int main() {
    cin >> N >> k;
    while (N--) {
        char sign; int p;
        cin >> sign >> p;
        if (sign == '+') insert_p(p);
        else if (sign == '-') erase_p(p);
    }

    for (auto &chair : Waitroom) {
        if (!chair.empty()) cout << chair.front() << '\n';
    }
    return 0;
}
