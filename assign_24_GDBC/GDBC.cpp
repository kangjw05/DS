#include <bits/stdc++.h>

using namespace std;

int main() {
    map<set<int>, vector<int>> mp;
    string ws;
    while (cin >> ws && ws != "$") {
        set<int> keySet;
        int n;
        if (ws == "R") {
            while (cin >> n) {
                if(n > 0) keySet.insert(n);
                else mp[keySet].push_back(n);
            }
            cin.clear();
        }
        else if (ws == "Q") {
            while (cin >> n) {
                if(n > 0) keySet.insert(n);
                else {
                    if (mp.find(keySet) != mp.end()) {
                        vector<int> disease = mp[keySet];
                        sort(disease.begin(), disease.end(), greater<int>());
                        for (int val : disease) {
                            cout << val << " ";
                        }
                        cout << "\n";
                    }
                    else cout << "None\n";
                }
            }
            cin.clear();
        }
    }
}