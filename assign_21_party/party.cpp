#include <bits/stdc++.h>

using namespace std;

// 노드 char - 'a'를 키로, 인접 노드 벡터로
map<int, vector<int>> graph;

// 각 장소에 몇 명이나 도달했는지 카운트
int visitedNum[26]; 

struct Runner {
    queue<int> que;
    bool visited[26]; 

    Runner(int start_node) {
        fill(visited, visited + 26, false);
        que.push(start_node);
        visited[start_node] = true;
        visitedNum[start_node]++;
    }

    bool move() {
        if (que.empty()) return false;

        int q_size = que.size();
        while (q_size--) {
            int cur = que.front();
            que.pop();

            for (int next : graph[cur]) {
                if (!visited[next]) {
                    visited[next] = true;
                    visitedNum[next]++; 
                    que.push(next);
                }
            }
        }
        return true;
    }
};

// 시간 계산: (step * 3) - 2
int calc_time(int step) {
    if (step == 0) return 0;
    return step * 3 - 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    vector<Runner> runners;
    for(int i=0; i<3; ++i) {
        char c;
        cin >> c;
        runners.emplace_back(c - 'a');
    }

    // 그래프 입력
    for (int i = 0; i < N; i++) {
        char u_char, v_char;
        cin >> u_char;
        int u = u_char - 'a'; 
        
        while (cin >> v_char && v_char != '$') {
            int v = v_char - 'a';
            // 양방향 연결 
            graph[u].push_back(v);
            graph[v].push_back(u); 
        }
    }

    int step = 0;
    while (true) {
        // 3명이 다 모인 장소 확인 (알파벳 순서대로 확인)
        for (int i = 0; i < 26; i++) {
            if (visitedNum[i] == 3) {
                cout << (char)(i + 'a') << "\n";
                cout << calc_time(step) << "\n";
                return 0;
            }
        }

        bool anyone_moved = false;
        for (auto& runner : runners) {
            if (runner.move()) {
                anyone_moved = true;
            }
        }

        if (!anyone_moved) {
            cout << "@\n-1\n";
            break;
        }

        step++;
    }

    return 0;
}