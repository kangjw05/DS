#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    // 5개의 그룹 2차원 백터 (Old-M, Old-F, Child, Adult-F, Adult-M)
    vector<vector<int>> groups(5);

    while (N--) {
        int id, age;
        char sex;
        cin >> id >> age >> sex;

        //old
        if (age > 60) groups[(sex == 'M' ? 0 : 1)].push_back(id); // 남성=0, 여성=1
        // Child
        else if (age <= 15) groups[2].push_back(id);
        // Adult
        else groups[(sex == 'F' ? 3 : 4)].push_back(id);  // 여성=3, 남성=4
    }

    // 이중 루프로 순서대로 출력
    for (const auto& group : groups) {
        for (int id : group) {
            cout << id << endl;
        }
    }

    return 0;
}