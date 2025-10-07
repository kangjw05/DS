#include <bits/stdc++.h>
#define PAIR pair<int, int>
#define REP(i, n) for(int i = 0; i < (n); ++i)
#define ALL(v) (v).begin(), (v).end()

using namespace std;

int main() {
    // N, k, t: 고객 수, 계산대 수, 현재 시간
    int N, k, t = 0;
    cin >> N >> k;

    // 대기줄
    queue<PAIR> waiting;
    // 계산대
    vector<PAIR> kiosks(k, {0, 0});
    // 퇴장 고객
    vector<int> exitCstmrs;

    REP(i, N) {
        int a, b; 
        cin >> a >> b;
        waiting.push({a, b});
    }

    while(exitCstmrs.size() < N) {
        // 끝난 고객 임시 저장 컨테이너
        vector<PAIR> finished;

        // 현재 시간에 계산 끝나는 고객 찾기
        REP(i, k) {
            if(kiosks[i].first != 0 && kiosks[i].second == t) {
                // 임시 저장 컨테이너에 저장 (id, 계산대 번호)
                finished.push_back({kiosks[i].first, i});
            }
        }
        // 끝난 고객이 있으면 정렬, 퇴장
        if(!finished.empty()) {
            // 계산대 번호가 큰 순서로 정렬
            sort(ALL(finished), [](const PAIR &x, const PAIR &y) {return x.second > y.second;});
            // 퇴장 고객에 추가, id 출력, 계산대 비움
            REP(i, finished.size()) {
                exitCstmrs.push_back(finished[i].first);
                cout << finished[i].first << endl;
                kiosks[finished[i].second] = {0, 0};
            }
        }
        // 빈 계산대에 고객 넣기
        REP(i, k) {
            if(kiosks[i].first == 0 && !waiting.empty()) {
                kiosks[i] = {waiting.front().first, t + waiting.front().second};
                waiting.pop();
            }
        }
        // 시간 증가
        t++;
    }
}