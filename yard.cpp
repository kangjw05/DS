#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)
#define ALL(x) (x).begin(),(x).end()

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;
    vector<vector<int>> yard(N);
    vector<int> size(N);

    // size 와 yard 입력
    REP(i, N) {
        int M;
        cin >> M;
        yard[i].resize(M);
        size[i] = M; 
        REP(j, M) {
            cin >> yard[i][j];
        }
    }

    while (1) {
        // 최대, 최소 높이
        int maxHeight = 0;
        int minHeight = 1e9;

        // 최대, 최소 높이 찾기
        REP(i, N) {
            int curSize = size[i];
            if (curSize > maxHeight) maxHeight = curSize;
            if (curSize < minHeight) minHeight = curSize;
        }

        // 최대 - 최소가 1 이하면 종료
        if (maxHeight - minHeight <= 1) break;

        // 최대 높이 중 무거운 컨테이너 찾기 (옮길 컨테이너가 있는 곳 = sourceIdx)
        int sourceIdx = -1;
        int maxWeight = -1;
        REP(i, N) {
            if (size[i] == maxHeight) {
                if(yard[i].back() > maxWeight) {
                    maxWeight = yard[i].back();
                    sourceIdx = i;
                }
            }
        }

        // 최소 높이인 곳 중 가장 앞에 있는 곳 찾기 (옮길 곳 = destIdx)
        int destIdx = -1;
        REP(i, N) {
            if (size[i] == minHeight) {
                destIdx = i;
                break;
            }
        }

        // 옮길 컨테이너
        int moveCont = yard[sourceIdx].back();
        // pop_back으로 뽑아내기
        yard[sourceIdx].pop_back();
        // push_back으로 넣기
        yard[destIdx].push_back(moveCont);

        // size 갱신
        size[sourceIdx]--;
        size[destIdx]++;
    }

    // 출력
    REP(i, N) {
        if (yard[i].empty()) {
            cout << "0\n";
        }
        else {
            REP(j, yard[i].size()) {
                cout << yard[i][j] << " ";
            }
            cout << "\n";
        }
    }

    return 0;
}